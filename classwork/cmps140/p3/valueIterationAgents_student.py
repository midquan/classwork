import learningAgents
import mdp
import util

class ValueIterationAgent(learningAgents.ValueEstimationAgent):
    """
    * Please read learningAgents.py before reading this.*

    A ValueIterationAgent takes a Markov decision process
    (see mdp.py) on initialization and runs value iteration
    for a given number of iterations using the supplied
    discount factor.
    """

    def __init__(self, mdp, discountRate = 0.9, iters = 100):
        """
        Your value iteration agent should take an mdp on
        construction, run the indicated number of iterations
        and then act according to the resulting policy.

        Some useful mdp methods you will use:
            mdp.getStates()
            mdp.getPossibleActions(state)
            mdp.getTransitionStatesAndProbs(state, action)
            mdp.getReward(state, action, nextState)
        """

        super().__init__()

        self.mdp = mdp
        self.discountRate = discountRate
        self.iters = iters
        self.values = util.Counter() # A Counter is a dict with default 0
        
        

        """
        Description:
        [Enter a description of what you did here.]
        
        This program gets the mdp and gets the qValues and maximizes the qValue at every given iteration. 
        Once it knows the correct policy it updates the values after the iterations. 
        """

        """ YOUR CODE HERE """
        qValues = []
        
        # Iterate over 0 - how many iterations iters has 
        for i in range(0, self.iters):
            # Create a counter class for updated Values instead of a dictionary 
            updatedValues = util.Counter()
            
            # For each next possible state, find the qValues and maxamize it 
            for nextState in self.mdp.getStates():
                # If no more possible actions update the value with the qValue of the current state. 
                if self.mdp.getPossibleActions(nextState) == []:
                    updatedValues[nextState] = self.getQValue(nextState) 
                else:     
                    # Create all qValues from each possible action from the given state 
                    qValues = [self.getQValue(nextState, actions) for actions in self.mdp.getPossibleActions(nextState)]
                    print ("Q-Values = ", qValues) 
                    
                    # If qValues is empty continue 
                    if qValues == []:
                        continue
                    # Else maxamize the qValues and update accordingly. Add the maxamized qValues to the Counter 
                    else: 
                        updatedValues[nextState] = max(qValues)
                        if(updatedValues[nextState] == max(qValues)):
                            print("updating Values") 
                            
            print ("updatedValues = ", updatedValues)         
            
            # Change the self.values to become the updatedVlalues after valueIteration 
            self.values = updatedValues
                
        """ END CODE """

    def getValue(self, state):
        """
        Return the value of the state (computed in __init__).
        """

        return self.values[state]

    def getQValue(self, state, action):
        """
        The q-value of the state action pair
        (after the indicated number of value iteration passes).
        Note that value iteration does not
        necessarily create this quantity and you may have
        to derive it on the fly.
        """

        """
        Q*(s,a) = Summation T(s,a,s') * [R(s,a,s') + Gamma * V*(s')] 
        Implented the formula given the transition states and pobability of each action. This gets the QValue of a given action. 
        """

        """ YOUR CODE HERE """
        sum = 0 

        # For each transition state we use the summation formula such that Q*(s,a) = Summation T(s,a,s') * [R(s,a,s') + Gamma * V*(s')] 
        
        # The states and probability are stored as a tuple in getTransitionStatesAndProbs 
        for (nextState, probability) in self.mdp.getTransitionStatesAndProbs(state, action):
            # R(s,a,s') =  self.mdp.getReward(state, action, nextState)
            # Gamma = self.discountRate 
            # V*(s') = self.getValue 
            sum += probability * (self.mdp.getReward(state, action, nextState) + (self.discountRate * self.getValue(nextState))) 
        return sum 
        # #util.raiseNotDefined()

        
        """ END CODE """

    def getPolicy(self, state):
        """
        The policy is the best action in the given state
        according to the values computed by value iteration.
        You may break ties any way you see fit.
        Note that if there are no legal actions, which is the case at the
        terminal state, you should return None.
        """

        """
        Compared what policy to use. If no legal actions, return None otherwise find best possible action with highest qValue. 
        Return that best possible Action. 
        
        """

        """ YOUR CODE HERE """
         
         # If no possible actions return None 
        if self.mdp.getPossibleActions is None: 
            return None 
        # Default bestAction is None 
        bestAction = None 
        # For every nextAction 
        for nextAction in self.mdp.getPossibleActions(state): 
            # For first action where bestAction is None or whenever the nextAction has a higher qValue make bestAction = nextAction 
            if bestAction is None or self.getQValue(state, nextAction) > self.getQValue(state, bestAction):
                bestAction = nextAction 
        # Return bestAction 
        return bestAction 
        
        #util.raiseNotDefined()
        """ END CODE """

    def getAction(self, state):
        """
        Returns the policy at the state (no exploration).
        """

        return self.getPolicy(state)
