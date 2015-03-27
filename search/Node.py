#Node.py

class Node:
    def __init__(self, state, action):
        self.state = state
        self.next = None
        self.action = action
        
    def getElm(self):
        return self.next
    
    def getNext():
        return self.next