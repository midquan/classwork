# Michael Quan
# CMPS 140 Spring 2019 

import random
from util import manhattanDistance
import game
import util
import math 

def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """

    return currentGameState.getScore()

class MultiAgentSearchAgent(game.Agent):
    """
    This class provides some common elements to all of your multi-agent searchers.
    Any methods defined here will be available to the
    MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.
    Please do not remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.
    It's only partially specified, and designed to be extended.
    Agent (game.py) is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0  # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn)
        self.treeDepth = int(depth)

class ReflexAgent(game.Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.
    You are welcome to change it in any way you see fit, so long as you don't touch the method headers.
    """

    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some game.Directions.X for some X in the set {North, South, West, East, Stop}
        """

        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        # *** Add more of your code here if you want to ***

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (oldFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """

        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPosition = successorGameState.getPacmanPosition()
        oldFood = currentGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        # *** Your Code Here ***
        
        # Base it on original score 
        score = successorGameState.getScore() 
        pacmanX = newPosition[0]
        pacmanY = newPosition[1] 
        
        pacmanPosition = (pacmanX, pacmanY) 
        ghostList = [] 
        newFood = successorGameState.getFood().asList() 
        for ghosts in newGhostStates: 
            #print("new ghost states = ", ghosts.getPosition) 
            whereGhosts = ghosts.getPosition() 
            #print("whereghosts[0] = ", whereGhosts[0])
            #print("whereghosts[1] = ", whereGhosts[1])
            ghostList.append((whereGhosts[0],whereGhosts[1]))
        
        # Score chances based on distance to the newest food with closeness, least penalized 
        if len(newFood) > 0: 
            score += -manhattanDistance(pacmanPosition, (newFood[0][0],newFood[0][1]))     
        
        #attempted to add scared time + distance to ghost however did not work for agent 
        # if(newScaredTimes[0] > 5):
            # score += newScaredTimes[0] 
            # if(pacmanPosition in ghostList): 
                # score += 50 
        # else: 
        
        # If pacman is in ghost penalize harshly 
        if(pacmanPosition in ghostList): 
            score += -1000 
        
        # If pacman is close to ghost also penalize 
        for currGhost in ghostList: 
            howFar = manhattanDistance(pacmanPosition, currGhost) 
            if(howFar < 2): 
                score += -500
            
            
        # print("sucessuccessorGameState = ", successorGameState)
        # print("newPosition = ", newPosition)
        # print("oldFood = ", oldFood)
        # print("newGhostStates = ", newGhostStates)
        # print("newScaredTimes = ", newScaredTimes) 
        # print(score) 
        return score 

        #return successorGameState.getScore()

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.treeDepth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
            Returns a list of legal actions for an agent
            agentIndex=0 means Pacman, ghosts are >= 1

        game.Directions.STOP:
            The stop direction, which is always legal

        gameState.generateSuccessor(agentIndex, action):
            Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
            Returns the total number of agents in the game
        """

        # *** Your Code Here ***
        
        possibleActions = gameState.getLegalActions(0) #list of legal pacman actions 
        
        # Initialize score as negative Infinity and default action as STOP 
        score = -math.inf
        action = game.Directions.STOP
        
        # Iterate through the possible actions 
        for nextAction in possibleActions: 
            #print(nextAction) 
            
            # Skip STOP if it exists 
            if nextAction == game.Directions.STOP: 
                continue
            else:     
                #print(nextState) 
                
                # Sucessor state generated from gameState 
                nextState = gameState.generateSuccessor(0, nextAction) 
                
                # Evaluates minimax tree by starting at max and finding value 
                scoreEvaluated = self.maxValue(nextState, 1 , self.treeDepth) 
                
                # If scoreEvaluted > score, make that action the next action it will take 
                if(scoreEvaluated > score): 
                    score = max(scoreEvaluated,score) 
                    action = nextAction 
        return action 

        #return self.evaluationFunction(gameState) 
        #util.raiseNotDefined()
        
        
    def maxValue(self, gameState,agent, depth):         
        #print("in maxValue in minimax") 
        
        # Recursion ends if loss, win, or depth = 0 which means top of tree 
        if(gameState.isLose() or gameState.isWin() or depth == 0): 
            return self.evaluationFunction(gameState) 
        # Maximum starts at negative Infinity 
        maximum = -math.inf
        
        # Get all possible actions for given agent and find amount of agents
        possibleActions = gameState.getLegalActions(agent)     
        numberAgents = gameState.getNumAgents() 
        
        # Iterate through the possible legal actions 
        for nextAction in possibleActions:
            #print(nextAction)
            
            # Skip STOP if it exists 
            if nextAction == game.Directions.STOP: 
                continue 
            # Otherwise loop through increment the agent and find remainder of it comapred to total agents  
            else: 
                nextAgent = agent + 1 
                nextState = gameState.generateSuccessor(agent, nextAction) 
                nextAgent %= numberAgents
                
                # Only one pacman agent thus find maximum of the next ghost agents 
                maximum = max(maximum,  self.minValue(nextState, nextAgent ,depth))
        return maximum 
        #print("legal actions = ", gameState.getLegalActions(0)) 
        
    def minValue(self, gameState,agent, depth): 
        #print("in minValue in minimax") 
        
        # Recursion ends if loss, win, or depth = 0 which means top of tree 
        if(gameState.isLose() or gameState.isWin() or depth == 0): 
            return self.evaluationFunction(gameState)
        
        # Minimum starts at Infinity 
        minimum = math.inf
        
        # Get all possible actions for given agent and find amount of agents
        possibleActions = gameState.getLegalActions(agent)
        numberAgents = gameState.getNumAgents() 
        
        # Iterate through the possible legal actions  
        for nextAction in possibleActions:
            #print(nextAction) 
            
            # Skip STOP if it exists 
            if nextAction == game.Directions.STOP: 
                continue 
            # Otherwise loop through increment the agent and find remainder of it comapred to total agents  
            else: 
                nextAgent = agent + 1
                nextState = gameState.generateSuccessor(agent, nextAction) 
                nextAgent %= numberAgents
                nextDepth = depth 
                
                # If nextAgent == 0 pacman agent thus find minimum of these maxValue and decrement depth 
                if nextAgent == 0:
                    nextDepth -= 1 
                    minimum = min(minimum,  self.maxValue(nextState, nextAgent , nextDepth))
                
                # If nextAgent != 0 this is a ghost agent continue to find minimum 
                else:
                    minimum = min(minimum,  self.minValue(nextState, nextAgent , nextDepth))        
        return minimum 
        #print("legal actions = ", gameState.getLegalActions(0)) 
    
class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.treeDepth and self.evaluationFunction
        """

        # *** Your Code Here ***
        
        possibleActions = gameState.getLegalActions(0) #list of legal pacman actions 
        
        # Initialize score as negative Infinity and default action as STOP 
        score = -math.inf
        action = game.Directions.STOP
        
        # Iterate through the possible actions 
        for nextAction in possibleActions: 
            #print(nextAction) 
            
            # Skip STOP if it exists 
            if nextAction == game.Directions.STOP: 
                continue
            else:     
                #print(nextState) 
                
                # Sucessor state generated from gameState 
                nextState = gameState.generateSuccessor(0, nextAction) 
                
                # Evaluates minimax tree by starting at max and finding value 
                scoreEvaluated = self.maxValue(nextState, 1 , self.treeDepth, -math.inf, math.inf) 
                
                # If scoreEvaluted > score, make that action the next action it will take 
                if(scoreEvaluated > score): 
                    score = max(scoreEvaluated,score) 
                    action = nextAction 
        return action 

        #return self.evaluationFunction(gameState) 
        #util.raiseNotDefined()
        
        
    def maxValue(self, gameState,agent, depth, alpha, beta):         
        #print("in maxValue in minimax") 
        
        # Recursion ends if loss, win, or depth = 0 which means top of tree 
        if(gameState.isLose() or gameState.isWin() or depth == 0): 
            return self.evaluationFunction(gameState) 
        # Maximum starts at negative Infinity 
        maximum = -math.inf
        
        # Get all possible actions for given agent and find amount of agents
        possibleActions = gameState.getLegalActions(agent)     
        numberAgents = gameState.getNumAgents() 
        
        # Iterate through the possible legal actions 
        for nextAction in possibleActions:
            #print(nextAction)
            
            # Skip STOP if it exists 
            if nextAction == game.Directions.STOP: 
                continue 
            # Otherwise loop through increment the agent and find remainder of it comapred to total agents  
            else: 
                nextAgent = agent + 1 
                nextState = gameState.generateSuccessor(agent, nextAction) 
                nextAgent %= numberAgents
                
                # Only one pacman agent thus find maximum of the next ghost agents 
                maximum = max(maximum,  self.minValue(nextState, nextAgent ,depth, alpha, beta))
                
                # If maximum >= beta prune rest of node and return maximum 
                if(maximum >= beta): 
                    return maximum 
                alpha = max(alpha,maximum) 
                
        return maximum 
        #print("legal actions = ", gameState.getLegalActions(0)) 
        
    def minValue(self, gameState,agent, depth, alpha, beta): 
        #print("in minValue in minimax") 
        
        # Recursion ends if loss, win, or depth = 0 which means top of tree 
        if(gameState.isLose() or gameState.isWin() or depth == 0): 
            return self.evaluationFunction(gameState)
        
        # Minimum starts at Infinity 
        minimum = math.inf
        
        # Get all possible actions for given agent and find amount of agents
        possibleActions = gameState.getLegalActions(agent)
        numberAgents = gameState.getNumAgents() 
        
        # Iterate through the possible legal actions  
        for nextAction in possibleActions:
            #print(nextAction) 
            
            # Skip STOP if it exists 
            if nextAction == game.Directions.STOP: 
                continue 
            # Otherwise loop through increment the agent and find remainder of it comapred to total agents  
            else: 
                nextAgent = agent + 1
                nextState = gameState.generateSuccessor(agent, nextAction) 
                nextAgent %= numberAgents
                nextDepth = depth 
                
                # If nextAgent == 0 pacman agent thus find minimum of these maxValue and decrement depth 
                if nextAgent == 0:
                    nextDepth -= 1 
                    minimum = min(minimum,  self.maxValue(nextState, nextAgent , nextDepth, alpha, beta))
                
                # If nextAgent != 0 this is a ghost agent continue to find minimum 
                else:
                    minimum = min(minimum,  self.minValue(nextState, nextAgent , nextDepth, alpha, beta)) 
                    
                    # If minimum <= alpha prune rest of nodes and return minimum
                    if(minimum <= alpha): 
                        return minimum 
                    beta = min(alpha,minimum) 
        return minimum 
        #print("legal actions = ", gameState.getLegalActions(0)) 
        
class ExpectimaxAgent(MultiAgentSearchAgent):
    """
    Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.treeDepth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """

        # *** Your Code Here ***
        util.raiseNotDefined()
        

def betterEvaluationFunction(currentGameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    """

    # *** Your Code Here ***
    util.raiseNotDefined()

class ContestAgent(MultiAgentSearchAgent):
    """
    Your agent for the mini-contest
    """

    def getAction(self, gameState):
        """
        Returns an action.
        You can use any method you want and search to any depth you want.
        Just remember that the mini-contest is timed, so you have to trade off speed and computation.

        Ghosts don't behave randomly anymore, but they aren't perfect either -- they'll usually
        just make a beeline straight towards Pacman (or away from him if they're scared!)
        """

        # *** Your Code Here ***
        util.raiseNotDefined()

# Abbreviation
better = betterEvaluationFunction
