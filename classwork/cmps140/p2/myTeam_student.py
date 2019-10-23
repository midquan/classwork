import random

from util import manhattanDistance
import game
import util
import math 
import captureAgents

#################
# Team creation #
#################

def createTeam(firstIndex, secondIndex, isRed,
        first = 'ReflexCaptureAgent', second = 'DummyAgent'):
    """
    This function should return a list of two agents that will form the
    team, initialized using firstIndex and secondIndex as their agent
    index numbers. isRed is True if the red team is being created, and
    will be False if the blue team is being created.

    As a potentially helpful development aid, this function can take
    additional string-valued keyword arguments ("first" and "second" are
    such arguments in the case of this function), which will come from
    the --redOpts and --blueOpts command-line arguments to capture.py.
    For the nightly contest, however, your team will be created without
    any extra arguments, so you should make sure that the default
    behavior is what you want for the nightly contest.
    """

    # The following line is an example only; feel free to change it.
    return [eval(first)(firstIndex), eval(second)(secondIndex)]

##########
# Agents #
##########

class AlphaBetaAgent(captureAgents.CaptureAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.treeDepth and self.evaluationFunction
        """

        # *** Your Code Here ***
        
        possibleActions = gameState.getLegalActions(0) #list of legal pacman actions 
        #print (possibleActions) 
        
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
                #print (nextState) 
                
                # Evaluates minimax tree by starting at max and finding value 
                scoreEvaluated = self.maxValue(nextState, 0 , 2, -math.inf, math.inf) 
                
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
        # if(gameState.isLose() or gameState.isWin() or depth == 0):
        if(depth == 0):
            return self.evaluate(gameState) 
        # Maximum starts at negative Infinity 
        maximum = -math.inf
        
        # Get all possible actions for given agent and find amount of agents
        #possibleActions = gameState.getLegalActions(agent)
        possibleActions = gameState.getLegalActions()
        print (possibleActions)
        numberAgents = gameState.getNumAgents() 
        print (numberAgents) 
        
        # Iterate through the possible legal actions 
        for nextAction in possibleActions:
            print(nextAction)
            
            # Skip STOP if it exists 
            if nextAction == game.Directions.STOP: 
                continue 
            # Otherwise loop through increment the agent and find remainder of it comapred to total agents  
            else: 
                nextAgent = agent + 1 
                nextState = gameState.generateSuccessor(self.index, nextAction) 
                print (nextState) 
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
        #if(gameState.isLose() or gameState.isWin() or depth == 0):
        if(depth == 0):
            return self.evaluate(gameState)
        
        # Minimum starts at Infinity 
        minimum = math.inf
        
        # Get all possible actions for given agent and find amount of agents
        possibleActions = gameState.getLegalActions()
        numberAgents = gameState.getNumAgents() 
        
        # Iterate through the possible legal actions  
        for nextAction in possibleActions:
            print(nextAction) 
            
            # Skip STOP if it exists 
            if nextAction == game.Directions.STOP: 
                continue 
            # Otherwise loop through increment the agent and find remainder of it comapred to total agents  
            else: 
                nextAgent = agent + 1
                print ("index", self.index)
                nextState = gameState.generateSuccessor(self.index, nextAction) 
                print ("nextAgent", nextAgent)
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
class ReflexCaptureAgent(captureAgents.CaptureAgent):
    """
    A base class for reflex agents that chooses score-maximizing actions
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.treeDepth and self.evaluationFunction
        """

        # *** Your Code Here ***
        
        possibleActions = gameState.getLegalActions(0) #list of legal pacman actions 
        #print (possibleActions) 
        
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
                #print (nextState) 
                
                # Evaluates minimax tree by starting at max and finding value 
                scoreEvaluated = self.maxValue(nextState, 0 ,4, -math.inf, math.inf) 
                
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
        # if(gameState.isLose() or gameState.isWin() or depth == 0):
        # if(depth == 0):
            # return self.evaluate(gameState) 
        # Maximum starts at negative Infinity 
        maximum = -math.inf
        
        # Get all possible actions for given agent and find amount of agents
        #possibleActions = gameState.getLegalActions(agent)
        possibleActions = gameState.getLegalActions()
        print (possibleActions)
        numberAgents = gameState.getNumAgents() 
        print (numberAgents) 
        
        # Iterate through the possible legal actions 
        for nextAction in possibleActions:
            if(depth == 0):
                return self.evaluate(gameState, nextAction) 
            print(nextAction)
            
            # Skip STOP if it exists 
            if nextAction == game.Directions.STOP: 
                continue 
            # Otherwise loop through increment the agent and find remainder of it comapred to total agents  
            else: 
                nextAgent = agent + 1 
                nextState = gameState.generateSuccessor(self.index, nextAction) 
                print (nextState) 
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
        #if(gameState.isLose() or gameState.isWin() or depth == 0):
        # if(depth == 0):
            # return self.evaluateFunction(gameState)
        
        # Minimum starts at Infinity 
        minimum = math.inf
        
        # Get all possible actions for given agent and find amount of agents
        possibleActions = gameState.getLegalActions()
        numberAgents = gameState.getNumAgents() 
        
        # Iterate through the possible legal actions  
        for nextAction in possibleActions:
            if(depth == 0):
                return self.evaluateFunction(gameState, nextAction)
            print(nextAction) 
            
            # Skip STOP if it exists 
            if nextAction == game.Directions.STOP: 
                continue 
            # Otherwise loop through increment the agent and find remainder of it comapred to total agents  
            else: 
                nextAgent = agent + 1
                nextState = gameState.generateSuccessor(self.index, nextAction) 
                print ("nextAgent", nextAgent)
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

    def getSuccessor(self, gameState, action):
        """
        Finds the next successor which is a grid position (location tuple).
        """

        successor = gameState.generateSuccessor(self.index, action)
        pos = successor.getAgentState(self.index).getPosition()
        if pos != util.nearestPoint(pos):
            # Only half a grid position was covered.
            return successor.generateSuccessor(self.index, action)
        else:
            return successor

    def evaluate(self, gameState, action):
        """
        Computes a linear combination of features and feature weights
        """

        features = self.getFeatures(gameState, action)
        weights = self.getWeights(gameState, action)
        return features * weights

    def getFeatures(self, gameState, action):
        """
        Returns a counter of features for the state
        """

        features = util.Counter()
        successor = self.getSuccessor(gameState, action)
        features['successorScore'] = self.getScore(successor)

        return features

    def getWeights(self, gameState, action):
        """
        Normally, weights do not depend on the gamestate.
        They can be either a counter or a dictionary.
        """

        return {'successorScore': 1.0}

class OffensiveReflexAgent(ReflexCaptureAgent):
    """
    A reflex agent that seeks food. This is an agent
    we give you to get an idea of what an offensive agent might look like,
    but it is by no means the best or only way to build an offensive agent.
    """
    features = util.Counter()
    def win(self,state, action):
          successor = self.getSuccessor(state, action)
          if(successor.isOver()):
                self.features['win'] = 9999999
          else:
                self.features['win'] = -100

    def scarredTimes(self, state, action):
        self.enemies = self.getOpponents(state)
        ghosts = [a for a in self.enemies if not state.getAgentState(a).isPacman]
        scaredTimes = [state.getAgentState(enemy).scaredTimer for enemy in ghosts]
        self.features['scarredTimes'] = max(scaredTimes)
    
    def distanceToFood(self, state, action):
        # features = util.Counter()
        successor = self.getSuccessor(state, action)
        # features['successorScore'] = self.getScore(successor)

        # Compute distance to the nearest food
        foodList = self.getFood(successor).asList()
        if len(foodList) > 0:  # This should always be True, but better safe than sorry
            myPos = successor.getAgentState(self.index).getPosition()
            minDistance = min([self.getMazeDistance(myPos, food) for food in foodList])
            self.features['distanceToFood'] = minDistance

    def foodLeft(self, state, action):
        # Set up Successor state
        successor = self.getSuccessor(state, action)
        # Get gets succ's food and outputs it to a list
        food = self.getFood(successor)
        foodList = food.asList()
        # Updates the features dict with the food left value.
        self.features['foodLeft'] = len(foodList)
    
    def numDefenders(self, state, action):
        # Set up Successor state
        successor = self.getSuccessor(state, action)
        # Make a list of all all the opponets on the board        
        enemies = [successor.getAgentState(i) for i in self.getOpponents(successor)]
        # defenders is a list of all the enemies ont the board who is not a pacman
        defenders = [a for a in enemies if not a.isPacman and a.getPosition() != None]
        # updates the numDefenders feature
        self.features['numDefenders'] = len(defenders)

    def successorScore(self, state, action):
        # Set up Successor state
        successor = self.getSuccessor(state, action)
        # updates the successorScore in the feat dict
        self.features['successorScore'] = self.getScore(successor)

    def ghosts_one_step_away(self, state, action):
        # Set up Successor state
        successor = self.getSuccessor(state, action)
        # Get our Agent's position on the board
        agentState = successor.getAgentState(self.index)
        x, y = agentState.getPosition()
        myPos = (x,y)
        # initialize the #-of-ghosts-1-step-away feat in the dict to 0
        # Not sure why we do this
        # self.features['#-of-ghosts-1-step-away'] = 0
        # Get the opponents on the board that is not a pacman
        enemies = [successor.getAgentState(i) for i in self.getOpponents(successor)]
        defenders = [a for a in enemies if not a.isPacman and a.getPosition() != None]
        # if there are defenders on the board we want to increment the value of the #-of-ghosts-1-step-away feature 
        if len(defenders) > 0:
            for defender in defenders:
                defPos = defender.getPosition()
                dist = abs(defPos[0]-myPos[0]) + abs(defPos[1]-myPos[1])
                if(dist == 1):
                    self.features['ghosts_one_step_away'] += 1

    def capsules(self, state):
          if state.isOnRedTeam(self.index):
            self.features['capsules'] = len(state.getBlueCapsules())
          self.features['capsules'] = len(state.getRedCapsules())
    
    def defendingcapsules(self, state):
          if not state.isOnRedTeam(self.index):
            self.features['defendingcapsules'] = len(state.getBlueCapsules())
          self.features['defendingcapsules'] = len(state.getRedCapsules())

    def opponentsFood(self, state):
          if state.isOnRedTeam(self.index):
            blueFood = state.getBlueFood().asList()
            self.features['opponentsFood'] = len(blueFood)

          redFood = state.getRedFood().asList()
          self.features['opponentsFood'] = len(redFood)

    def getFeatures(self, state, action):
        self.features["bias"] = 1.0
        self.features['distanceToFood'] = 0
        self.features['foodLeft'] = 0
        # self.features['numDefenders'] = 0
        self.features['successorScore'] = 0
        # self.features['ghosts_one_step_away'] = 0
        self.features['capsules'] = 0
        # self.features['defendingcapsules'] = 0
        self.features['opponentsFood'] = 0
        self.features['win'] = 0

        self.distanceToFood(state,action)
        self.foodLeft(state,action)
        # self.numDefenders(state, action)
        self.successorScore(state,action)
        # self.ghosts_one_step_away(state,action)
        self.capsules(state)
        # self.defendingcapsules(state)
        self.opponentsFood(state)

        self.win(state,action)

        self.scarredTimes(state,action)
        self.features.divideAll(10.0)
        # print("-"*150)
        # print(self.features)
        # print("-"*150)

        return self.features

    def getWeights(self, gameState, action):
          
        return {
            'distanceToFood': -1,
            'foodLeft': -1,
            'numDefenders': -1,
            'successorScore': 100,
            'ghosts_one_step_away': 50,
            'capsules': -50,
            'defendingcapsules': 25,
            'opponentsFood': -50,
            'win': 99,
            'scarredTimes': 25
        }        
        
class DummyAgent(captureAgents.CaptureAgent):
    """
    A Dummy agent to serve as an example of the necessary agent structure.
    You should look at baselineTeam.py for more details about how to
    create an agent as this is the bare minimum.
    """

    def registerInitialState(self, gameState):
        """
        This method handles the initial setup of the
        agent to populate useful fields (such as what team
        we're on). 
        
        A distanceCalculator instance caches the maze distances
        between each pair of positions, so your agents can use:
        self.distancer.getDistance(p1, p2)

        IMPORTANT: This method may run for at most 15 seconds.
        """

        """ 
        Make sure you do not delete the following line. If you would like to
        use Manhattan distances instead of maze distances in order to save
        on initialization time, please take a look at
        CaptureAgent.registerInitialState in captureAgents.py. 
        """

        captureAgents.CaptureAgent.registerInitialState(self, gameState)

        """ 
        Your initialization code goes here, if you need any.
        """

    def chooseAction(self, gameState):
        """
        Picks among actions randomly.
        """
        actions = gameState.getLegalActions(self.index)

        """ 
        You should change this in your own agent.
        """

        return random.choice(actions)
