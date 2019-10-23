"""
In this file, you will implement generic search algorithms which are called by Pacman agents.
"""

import util

# Called by search.depthFirstSearch.
def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first [p 85].

    Your search algorithm needs to return a list of actions that reaches
    the goal.  Make sure to implement a graph search algorithm [Fig. 3.7].

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start: %s" % (str(problem.startingState())))
    print("Is the start a goal?: %s" % (problem.isGoal(problem.startingState())))
    print("Start's successors: %s" % (problem.successorStates(problem.startingState())))
    """

    # *** Your Code Here ***
    
    print("Start: %s" % (str(problem.startingState())))
    print("Is the start a goal?: %s" % (problem.isGoal(problem.startingState())))
    print("Start's successors: %s" % (problem.successorStates(problem.startingState())))
    
    # start = problem.startingState() 
    
    # if problem.isGoal(start):
        # return None   
        
    # successors = [] 
    # directions = [] 
    # explored = [start] 
    # path = []
    
    # for next in problem.successorStates(start):
        # successors.append(next) 
        
    # while len(successors) > 0: 
        # next = successors[-1]
        # if not next[0] in explored: 
            # explored.append(next[0])
            # directions.append(next[1][:])
            # print(next[1]) 
            # if problem.isGoal(next[0]):
                # return directions 
            # for expanding in problem.successorStates(next[0]):
                # successors.append(expanding)
        # else: 
            # successors.pop()
            # if next == directions[-1]:
                # directions.pop()
                
    # currentPath = []
    # explored = [problem.startingState()]
    # fringe = util.Stack 

    # for move in problem.successorStates(problem.startingState()):
        # fringe.push(move)

    # while len(fringe) > 0:
        # move = fringe[-1]
        # if not move[0] in explored:
            # explored.append(move[0])
            # currentPath.append(move)
            # if problem.isGoal(move[0]):
                # # path = []
                # # for _, direction, _ in currentPath:
                    # # path.append(direction)
                # return currentPath[1]
            # for nextMove in problem.successorStates(move[0]):
                # fringe.push(nextMove)
        # else:
            # fringe.pop()
            # if move == currentPath[-1]:
                # currentPath.pop()

# Called by search.breadthFirstSearch.
def breadthFirstSearch(problem):
    """
    Search the shallowest nodes in the search tree first. [p 81]
    """

    # *** Your Code Here ***
    util.raiseNotDefined()

# Called by search.uniformCostSearch.
def uniformCostSearch(problem):
    """
    Search the node of least total cost first.
    """

    # *** Your Code Here ***
    util.raiseNotDefined()

# Called by search.aStarSearch.
def aStarSearch(problem, heuristic):
    """
    Search the node that has the lowest combined cost and heuristic first.
    """

    # *** Your Code Here ***
    util.raiseNotDefined()
