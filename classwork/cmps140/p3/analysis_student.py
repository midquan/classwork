######################
# ANALYSIS QUESTIONS #
######################

# Change these default values to obtain the specified policies through
# value iteration.

def question2():
    """
    Changed noise so that the chance of them falling off the bridge is 0. This means they will always choose to go across the bridge.
    There is no chance of them falling when answer noise is 0. 
    """

    answerDiscount = 0.9
    answerNoise = 0.0

    """ YOUR CODE HERE """

    """ END CODE """

    return answerDiscount, answerNoise

def question3a():
    """
    To make it prioritize the close exit, every living move must be penalized accordingly. This allows it to focus on getting out rather then getting to the better exit.
    I put a negative living reward so that it prioritized escaping over everything else. 
    """

    answerDiscount = 0.9
    answerNoise = 0.2
    answerLivingReward = -3.0 

    """ YOUR CODE HERE """

    """ END CODE """

    return answerDiscount, answerNoise, answerLivingReward
    # If not possible, return 'NOT POSSIBLE'

def question3b():
    """
    To make it prioritize the close exit, but avoid the cliff, I penalized living less, but I also made it less important for the answer. 
    This allows for it to go through the other way yet still prioritize the close exit. 
    
    """

    answerDiscount = 0.5
    answerNoise = 0.2
    answerLivingReward = -1.0 

    """ YOUR CODE HERE """

    """ END CODE """

    return answerDiscount, answerNoise, answerLivingReward
    # If not possible, return 'NOT POSSIBLE'

def question3c():
    """
    To have it prioritize the far exit, but try to get there risking the cliff, I added a penalty for living to ensure that. 
    """

    answerDiscount = 0.9 
    answerNoise = 0.2
    answerLivingReward = -1.0

    """ YOUR CODE HERE """

    """ END CODE """

    return answerDiscount, answerNoise, answerLivingReward
    # If not possible, return 'NOT POSSIBLE'

def question3d():
    """
    The base code already ensures that it will prioritize the distant exit, yet still avoid cliff if possible. 
    """

    answerDiscount = 0.9
    answerNoise = 0.2
    answerLivingReward = 0.0

    """ YOUR CODE HERE """

    """ END CODE """

    return answerDiscount, answerNoise, answerLivingReward
    # If not possible, return 'NOT POSSIBLE'

def question3e():
    """
    Prioritize Living over absolutely everything, so make the living reward huge. 
    """

    answerDiscount = 0.9
    answerNoise = 0.2
    answerLivingReward = 50.0 

    """ YOUR CODE HERE """

    """ END CODE """

    return answerDiscount, answerNoise, answerLivingReward
    # If not possible, return 'NOT POSSIBLE'

def question6():
    """
    Description:
    [Enter a description of what you did here.]
    """

    answerEpsilon = None
    answerLearningRate = None

    """ YOUR CODE HERE """

    """ END CODE """

    return answerEpsilon, answerLearningRate
    # If not possible, return 'NOT POSSIBLE'

if __name__ == '__main__':
    questions = [
        question2,
        question3a,
        question3b,
        question3c,
        question3d,
        question3e,
        question6,
    ]

    print('Answers to analysis questions:')
    for question in questions:
        response = question()
        print('    Question %-10s:\t%s' % (question.__name__, str(response)))
