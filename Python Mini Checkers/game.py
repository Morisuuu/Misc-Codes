import tkinter
import time
import _thread
import copy
import math
import random
import datetime

class CheckerGame():
    def __init__(self):
        self.lock = _thread.allocate_lock()
        self.board = self.initBoard()
        self.playerTurn = self.whoGoFirst()
        self.difficulty = self.getDifficulty()
        self.AIPlayer = AIPlayer(self, self.difficulty)
        self.GUI = BoardGUI(self)

        if not self.isPlayerTurn():
            _thread.start_new_thread(self.AIMakeMove, ())

        self.GUI.startGUI()

    def whoGoFirst(self):
        ans = input("Want to go first? (Y/N) ")
        return ans == "Y" or ans == "y"

    def getDifficulty(self):
        ans = eval(input("What level of difficulty? (1 - Easy, 2  - Not so Easy, 3 - HARD) "))
        while not (ans == 1 or ans == 2 or ans == 3):
            print("Invalid input, please enter a value between 1 and 3")
            ans = eval(input("What level of difficulty? (1 - Easy, 2  - Not so Easy, 3 - HARD) "))
        return ans

    def initBoard(self):
        board = [[0]*6 for _ in range(6)]
        self.playerCheckers = set()
        self.opponentCheckers = set()
        self.checkerPositions = {}
        for i in range(6):
            self.playerCheckers.add(i + 1)
            self.opponentCheckers.add(-(i + 1))
            if i % 2 == 0:
                board[1][i] = -(i + 1)
                board[5][i] = i + 1
                self.checkerPositions[-(i + 1)] = (1, i)
                self.checkerPositions[i + 1] = (5, i)
            else:
                board[0][i] = -(i + 1)
                board[4][i] = i + 1
                self.checkerPositions[-(i + 1)] = (0, i)
                self.checkerPositions[i + 1] = (4, i)

        self.boardUpdated = True

        return board

    def getBoard(self):
        return self.board

    def printBoard(self):
        for i in range(len(self.board)):
            for j in range(len(self.board[i])):
                check = self.board[i][j]
                if (check < 0):
                    print(check,end=' ')
                else:
                    print(' ' + str(check),end=' ')

            print()

    def isBoardUpdated(self):
        return self.boardUpdated

    def setBoardUpdated(self):
        self.lock.acquire()
        self.boardUpdated = True
        self.lock.release()

    def completeBoardUpdate(self):
        self.lock.acquire()
        self.boardUpdated = False
        self.lock.release()

    def isPlayerTurn(self):
        return self.playerTurn

    def changePlayerTurn(self):
        if self.playerTurn and self.opponentCanContinue():
            self.playerTurn = False
        elif not self.playerTurn and self.playerCanContinue():
            self.playerTurn = True

    def move(self, oldrow, oldcol, row, col):
        if not self.isValidMove(oldrow, oldcol, row, col, self.playerTurn):
            return

        if self.playerTurn and not ([oldrow, oldcol, row, col] in self.getPossiblePlayerActions()):
            return

        self.makeMove(oldrow, oldcol, row, col)
        _thread.start_new_thread(self.next, ())

    def next(self):
        if self.isGameOver():
            self.getGameSummary()
            return
        self.changePlayerTurn()
        if self.playerTurn:
            return
        else:
            self.AIMakeMove()

    def AIMakeMove(self):
        self.GUI.pauseGUI()
        oldrow, oldcol, row, col = self.AIPlayer.getNextMove()
        self.move(oldrow, oldcol, row, col)
        self.GUI.resumeGUI()

    def makeMove(self, oldrow, oldcol, row, col):
        toMove = self.board[oldrow][oldcol]
        self.checkerPositions[toMove] = (row, col)

        self.board[row][col] = self.board[oldrow][oldcol]
        self.board[oldrow][oldcol] = 0

        if abs(oldrow - row) == 2:
            toRemove = self.board[(oldrow + row) // 2][(oldcol + col) // 2]
            if toRemove > 0:
                self.playerCheckers.remove(toRemove)
            else:
                self.opponentCheckers.remove(toRemove)
            self.board[(oldrow + row) // 2][(oldcol + col) // 2] = 0
            self.checkerPositions.pop(toRemove, None)

        self.setBoardUpdated()

    def getPossiblePlayerActions(self):
        checkers = self.playerCheckers
        regularDirs = [[-1, -1], [-1, 1]]
        captureDirs = [[-2, -2], [-2, 2]]

        regularMoves = []
        captureMoves = []
        for checker in checkers:
            oldrow = self.checkerPositions[checker][0]
            oldcol = self.checkerPositions[checker][1]
            for dir in regularDirs:
                if self.isValidMove(oldrow, oldcol, oldrow+dir[0], oldcol+dir[1], True):
                    regularMoves.append([oldrow, oldcol, oldrow+dir[0], oldcol+dir[1]])
            for dir in captureDirs:
                if self.isValidMove(oldrow, oldcol, oldrow+dir[0], oldcol+dir[1], True):
                    captureMoves.append([oldrow, oldcol, oldrow+dir[0], oldcol+dir[1]])
        if captureMoves:
            return captureMoves
        else:
            return regularMoves

    def isValidMove(self, oldrow, oldcol, row, col, playerTurn):
        if oldrow < 0 or oldrow > 5 or oldcol < 0 or oldcol > 5 \
                or row < 0 or row > 5 or col < 0 or col > 5:
            return False
        if self.board[oldrow][oldcol] == 0:
            return False
        if self.board[row][col] != 0:
            return False

        if playerTurn:
            if row - oldrow == -1:
                return abs(col - oldcol) == 1
            elif row - oldrow == -2:
                return (col - oldcol == -2 and self.board[row+1][col+1] < 0) \
                       or (col - oldcol == 2 and self.board[row+1][col-1] < 0)
            else:
                return False
        else:
            if row - oldrow == 1:
                return abs(col - oldcol) == 1
            elif row - oldrow == 2:
                return (col - oldcol == -2 and self.board[row-1][col+1] > 0) \
                       or (col - oldcol == 2 and self.board[row-1][col-1] > 0)
            else:
                return False

    def playerCanContinue(self):
        directions = [[-1, -1], [-1, 1], [-2, -2], [-2, 2]]
        for checker in self.playerCheckers:
            position = self.checkerPositions[checker]
            row = position[0]
            col = position[1]
            for dir in directions:
                if self.isValidMove(row, col, row + dir[0], col + dir[1], True):
                    return True
        return False

    def opponentCanContinue(self):
        directions = [[1, -1], [1, 1], [2, -2], [2, 2]]
        for checker in self.opponentCheckers:
            position = self.checkerPositions[checker]
            row = position[0]
            col = position[1]
            for dir in directions:
                if self.isValidMove(row, col, row + dir[0], col + dir[1], False):
                    return True
        return False

    def isGameOver(self):
        if len(self.playerCheckers) == 0 or len(self.opponentCheckers) == 0:
            return True
        else:
            return (not self.playerCanContinue()) and (not self.opponentCanContinue())

    def getGameSummary(self):
        self.GUI.pauseGUI()
        print("Game Over!")
        playerNum = len(self.playerCheckers)
        opponentNum = len(self.opponentCheckers)
        if (playerNum > opponentNum):
            print("You won by {0:d} checkers! Congratulation!".format(playerNum - opponentNum))
        elif (playerNum < opponentNum):
            print("Computer won by {0:d} checkers! Try again!".format(opponentNum - playerNum))
        else:
            print("Draw! Try again!")

class BoardGUI():
    def __init__(self, game):
        self.game = game
        self.ROWS = 6
        self.COLS = 6
        self.WINDOW_WIDTH = 600
        self.WINDOW_HEIGHT = 600
        self.col_width = self.WINDOW_WIDTH / self.COLS
        self.row_height = self.WINDOW_HEIGHT / self.ROWS

        self.initBoard()

    def initBoard(self):
        self.root = tkinter.Tk()
        self.c = tkinter.Canvas(self.root, width=self.WINDOW_WIDTH, height=self.WINDOW_HEIGHT,
                                borderwidth=5, background='white')
        self.c.pack()
        self.board = [[0]*self.COLS for _ in range(self.ROWS)]
        self.tiles = [[None for _ in range(self.COLS)] for _ in range(self.ROWS)]

        for i in range(6):
            for j in range(6):
                if (i + j) % 2 == 1:
                    self.c.create_rectangle(i * self.row_height, j * self.col_width,
                                        (i+1) * self.row_height, (j+1) * self.col_width, fill="gray", outline="gray")

        for i in range(6):
            self.c.create_line(0, self.row_height * i, self.WINDOW_WIDTH, self.row_height * i, width=2)
            self.c.create_line(self.col_width * i, 0, self.col_width * i, self.WINDOW_HEIGHT, width=2)

        self.updateBoard()

        self.checkerSelected = False
        self.clickData = {"row": 0, "col": 0, "checker": None}

        self.c.bind("<Button-1>", self.processClick)

        self.root.after(1000, self.updateBoard)


    def startGUI(self):
        self.root.mainloop()

    def pauseGUI(self):
        self.c.bind("<Button-1>", '')

    def resumeGUI(self):
        self.c.bind("<Button-1>", self.processClick)
        
    def updateBoard(self):
        if self.game.isBoardUpdated():
            newBoard = self.game.getBoard()
            for i in range(len(self.board)):
                for j in range(len(self.board[0])):
                    if self.board[i][j] != newBoard[i][j]:
                        self.board[i][j] = newBoard[i][j]
                        self.c.delete(self.tiles[i][j])
                        self.tiles[i][j] = None
                        if newBoard[i][j] < 0:
                            self.tiles[i][j] = self.c.create_oval(j*self.col_width+10, i*self.row_height+10,
                                                              (j+1)*self.col_width-10, (i+1)*self.row_height-10,
                                                              fill="black")
                        elif newBoard[i][j] > 0:
                            self.tiles[i][j] = self.c.create_oval(j*self.col_width+10, i*self.row_height+10,
                                                                  (j+1)*self.col_width-10, (i+1)*self.row_height-10,
                                                                  fill="red")
                        else:
                            continue

                        self.c.tag_raise(self.tiles[i][j])
            self.game.completeBoardUpdate()
        self.root.after(1000, self.updateBoard)
        
    def isCurrentPlayerChecker(self, row, col):
        return self.game.isPlayerTurn() == (self.board[row][col] > 0)

    def processClick(self, event):
        col = int(event.x // self.col_width)
        row = int(event.y // self.row_height)
        if not self.checkerSelected:
            if self.board[row][col] != 0 and self.isCurrentPlayerChecker(row, col):
                self.clickData["row"] = row
                self.clickData["col"] = col
                self.clickData["color"] = self.c.itemcget(self.tiles[row][col], 'fill')

                self.c.delete(self.tiles[row][col])
                self.tiles[row][col] = self.c.create_oval(col*self.col_width+10, row*self.row_height+10,
                                                         (col+1)*self.col_width-10, (row+1)*self.row_height-10,
                                                          fill="green")
                self.checkerSelected = True

            else:
                return

        else:
            oldrow = self.clickData["row"]
            oldcol = self.clickData["col"]
            self.c.delete(self.tiles[oldrow][oldcol])
            self.tiles[oldrow][oldcol] = self.c.create_oval(oldcol*self.col_width+10, oldrow*self.row_height+10,
                                                            (oldcol+1)*self.col_width-10, (oldrow+1)*self.row_height-10,
                                                            fill=self.clickData["color"])

            self.game.move(self.clickData["row"], self.clickData["col"],row, col)
            self.checkerSelected = False

class AIPlayer():
    def __init__(self, game, difficulty):
        self.game = game
        self.difficulty = difficulty

    def getNextMove(self):
        if self.difficulty == 1:
            return self.getNextMoveEasy()
        elif self.difficulty == 2:
            return self.getNextMoveMedium()
        else:
            return self.getNextMoveHard()

    def getNextMoveEasy(self):
        state = AIGameState(self.game)
        moves = state.getActions(False)
        index = random.randrange(len(moves))
        chosenMove = moves[index]
        return chosenMove[0], chosenMove[1], chosenMove[2], chosenMove[3]

    def getNextMoveMedium(self):
        state = AIGameState(self.game)
        nextMove = self.alphaBetaSearch(state, 5)
        return nextMove[0], nextMove[1], nextMove[2], nextMove[3]

    def getNextMoveHard(self):
        state = AIGameState(self.game)
        depthLimit = self.computeDepthLimit(state)
        nextMove = self.alphaBetaSearch(state, depthLimit)
        return nextMove[0], nextMove[1], nextMove[2], nextMove[3]

    def computeDepthLimit(self, state):
        numcheckers = len(state.AICheckers) + len(state.humanCheckers)
        return 26 - numcheckers

    def alphaBetaSearch(self, state, depthLimit):
        self.currentDepth = 0
        self.maxDepth = 0
        self.numNodes = 0
        self.maxPruning = 0
        self.minPruning = 0

        self.bestMove = []
        self.depthLimit = depthLimit

        starttime = datetime.datetime.now()
        v = self.maxValue(state, -1000, 1000, self.depthLimit)


        print("Time = " + str(datetime.datetime.now() - starttime))
        print("selected value " + str(v))
        print("(1) max depth of the tree = {0:d}".format(self.maxDepth))
        print("(2) total number of nodes generated = {0:d}".format(self.numNodes))
        print("(3) number of times pruning occurred in the MAX-VALUE() = {0:d}".format(self.maxPruning))
        print("(4) number of times pruning occurred in the MIN-VALUE() = {0:d}".format(self.minPruning))

        return self.bestMove

    def maxValue(self, state, alpha, beta, depthLimit):
        if state.terminalTest():
            return state.computeUtilityValue()
        if depthLimit == 0:
            return state.computeHeuristic()

        self.currentDepth += 1
        self.maxDepth = max(self.maxDepth, self.currentDepth)
        self.numNodes += 1

        v = -math.inf
        for a in state.getActions(False):
            captured = state.applyAction(a)
            if state.humanCanContinue():
                next = self.minValue(state, alpha, beta, depthLimit - 1)
            else:
                next = self.maxValue(state, alpha, beta, depthLimit - 1)
            if next > v:
                v = next
                if depthLimit == self.depthLimit:
                    self.bestMove = a
            state.resetAction(a, captured)

            if v >= beta:
                self.maxPruning += 1
                self.currentDepth -= 1
                return v
            alpha = max(alpha, v)

        self.currentDepth -= 1

        return v

    def minValue(self, state, alpha, beta, depthLimit):
        if state.terminalTest():
            return state.computeUtilityValue()
        if depthLimit == 0:
            return state.computeHeuristic()

        self.currentDepth += 1
        self.maxDepth = max(self.maxDepth, self.currentDepth)
        self.numNodes += 1

        v = math.inf
        for a in state.getActions(True):
            captured = state.applyAction(a)
            if state.AICanContinue():
                next = self.maxValue(state, alpha, beta, depthLimit - 1)
            else:
                next = self.minValue(state, alpha, beta, depthLimit - 1)
            if next < v:
                v = next
            state.resetAction(a, captured)

            if v <= alpha:
                self.minPruning += 1
                self.currentDepth -= 1
                return v
            beta = min(beta, v)

        self.currentDepth -= 1
        return v

class AIGameState():
    def __init__(self, game):
        self.board = copy.deepcopy(game.getBoard())

        self.AICheckers = set()
        for checker in game.opponentCheckers:
            self.AICheckers.add(checker)
        self.humanCheckers = set()
        for checker in game.playerCheckers:
            self.humanCheckers.add(checker)
        self.checkerPositions = {}
        for checker, position in game.checkerPositions.items():
            self.checkerPositions[checker] = position

    def humanCanContinue(self):
        directions = [[-1, -1], [-1, 1], [-2, -2], [-2, 2]]
        for checker in self.humanCheckers:
            position = self.checkerPositions[checker]
            row = position[0]
            col = position[1]
            for dir in directions:
                if self.isValidMove(row, col, row + dir[0], col + dir[1], True):
                    return True
        return False

    def AICanContinue(self):
        directions = [[1, -1], [1, 1], [2, -2], [2, 2]]
        for checker in self.AICheckers:
            position = self.checkerPositions[checker]
            row = position[0]
            col = position[1]
            for dir in directions:
                if self.isValidMove(row, col, row + dir[0], col + dir[1], False):
                    return True
        return False

    def terminalTest(self):
        if len(self.humanCheckers) == 0 or len(self.AICheckers) == 0:
            return True
        else:
            return (not self.AICanContinue()) and (not self.humanCanContinue())

    def isValidMove(self, oldrow, oldcol, row, col, humanTurn):
        if oldrow < 0 or oldrow > 5 or oldcol < 0 or oldcol > 5 \
                or row < 0 or row > 5 or col < 0 or col > 5:
            return False
        if self.board[oldrow][oldcol] == 0:
            return False
        if self.board[row][col] != 0:
            return False

        if humanTurn:
            if row - oldrow == -1:
                return abs(col - oldcol) == 1
            elif row - oldrow == -2:
                return (col - oldcol == -2 and self.board[row+1][col+1] < 0) \
                       or (col - oldcol == 2 and self.board[row+1][col-1] < 0)
            else:
                return False
        else:
            if row - oldrow == 1:
                return abs(col - oldcol) == 1
            elif row - oldrow == 2:
                return (col - oldcol == -2 and self.board[row-1][col+1] > 0) \
                       or (col - oldcol == 2 and self.board[row-1][col-1] > 0)
            else:
                return False

    def computeUtilityValue(self):
        utility = (len(self.AICheckers) - len(self.humanCheckers)) * 500 \
                  + len(self.AICheckers) * 50
        return utility

    def computeHeuristic(self):
        heurisitc = (len(self.AICheckers) - len(self.humanCheckers)) * 50 \
                    + self.countSafeAICheckers() * 10 + len(self.AICheckers)
        return heurisitc

    def countSafeAICheckers(self):
        count = 0
        for AIchecker in self.AICheckers:
            AIrow = self.checkerPositions[AIchecker][0]
            AIcol = self.checkerPositions[AIchecker][1]
            safe = True
            if not (AIcol == 0 or AIcol == len(self.board[0])):
                for humanchecker in self.humanCheckers:
                    if AIrow < self.checkerPositions[humanchecker][0]:
                        safe = False
                        break
            if safe:
                count += 1
        return count

    def getActions(self, humanTurn):
        if humanTurn:
            checkers = self.humanCheckers
            regularDirs = [[-1, -1], [-1, 1]]
            captureDirs = [[-2, -2], [-2, 2]]
        else:
            checkers = self.AICheckers
            regularDirs = [[1, -1], [1, 1]]
            captureDirs = [[2, -2], [2, 2]]

        regularMoves = []
        captureMoves = []
        for checker in checkers:
            oldrow = self.checkerPositions[checker][0]
            oldcol = self.checkerPositions[checker][1]
            for dir in regularDirs:
                if self.isValidMove(oldrow, oldcol, oldrow+dir[0], oldcol+dir[1], humanTurn):
                    regularMoves.append([oldrow, oldcol, oldrow+dir[0], oldcol+dir[1]])
            for dir in captureDirs:
                if self.isValidMove(oldrow, oldcol, oldrow+dir[0], oldcol+dir[1], humanTurn):
                    captureMoves.append([oldrow, oldcol, oldrow+dir[0], oldcol+dir[1]])

        if captureMoves:
            return captureMoves
        else:
            return regularMoves

    def applyAction(self, action):
        oldrow = action[0]
        oldcol = action[1]
        row = action[2]
        col = action[3]
        captured = 0

        toMove = self.board[oldrow][oldcol]
        self.checkerPositions[toMove] = (row, col)
        self.board[row][col] = toMove
        self.board[oldrow][oldcol] = 0

        if abs(oldrow - row) == 2:
            captured = self.board[(oldrow + row) // 2][(oldcol + col) // 2]
            if captured > 0:
                self.humanCheckers.remove(captured)
            else:
                self.AICheckers.remove(captured)
            self.board[(oldrow + row) // 2][(oldcol + col) // 2] = 0
            self.checkerPositions.pop(captured, None)

        return captured

    def resetAction(self, action, captured):
        oldrow = action[0]
        oldcol = action[1]
        row = action[2]
        col = action[3]

        toMove = self.board[row][col]
        self.checkerPositions[toMove] = (oldrow, oldcol)
        self.board[oldrow][oldcol] = toMove
        self.board[row][col] = 0

        if abs(oldrow - row) == 2:
            if captured > 0:
                self.humanCheckers.add(captured)
            else:
                self.AICheckers.add(captured)
            self.board[(oldrow + row) // 2][(oldcol + col) // 2] = captured
            self.checkerPositions[captured] = ((oldrow + row) // 2, (oldcol + col) // 2)

    def printBoard(self):
        for i in range(len(self.board)):
            for j in range(len(self.board[i])):
                check = self.board[i][j]
                if (check < 0):
                    print(check,end=' ')
                else:
                    print(' ' + str(check),end=' ')

            print()
        print('------------------------')


game = CheckerGame()
