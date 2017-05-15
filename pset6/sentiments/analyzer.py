import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        
        self.positives = set()
        self.negatives = set()
        
        # Puts positive words in the set
        file = open(positives, "r")
        for line in file:
            if line.startswith(";") or line.startswith(" ") is False:
                self.positives.add(line.rstrip(" \n"))
        file.close()
        
        # Puts negative words in the set
        file = open(negatives, "r")
        for line in file:
            if line.startswith(";") or line.startswith(" ") is False:
                self.negatives.add(line.strip(" \n"))
        file.close()
        

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        score = 0
        
        for token in tokens:
            if token.lower() in self.positives:
                score += 1
            elif token.lower() in self.negatives:
                score -= 1
                
        return score
            
        
        return 0
