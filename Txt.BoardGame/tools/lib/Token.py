
import re

# represents a token entry in token db
class Token:
	def __init__(self):
		pass
		
	def valid(self):
		if(re.match('[0-2]{8}', self.directions) == None):
			print ('Invalid token: {0} directions: {1}\n'.format(self.idno, self.directions))
			return False
		elif 0 > int(self.attack) > 3:
			print ('Invalid token: {0} attack: {1}\n'.format(self.idno, self.attack))
			return False
		elif 0 > int(self.defense) > 3:
			print ('Invalid token: {0} attack: {1}\n'.format(self.idno, self.defense))
			return False
		elif re.match('[0-1]{8}', self.directions) and int(self.attack) > 0:
			print ('Invalid token: {0} has attack but not required: {1}\n'.format(self.idno, self.defense))
			return False
		#elf if check rest
		else:
			return True	
			
	def calcValue(self):
		sum = 0
		sum += int(self.attack)
		sum += int(self.defense)
		for i, c in enumerate(self.directions):
			sum += int(c)
		return sum


# TokenDB
class TokenDB:
    
    def __init__(self, fileName):
        self.file = open(fileName, "r")
        self.tokenSet = set()
    
    def __del__(self):
        self.file.close()
    
    def foreach(self, func):
        #svg.file.seek(0)
        lineno = 0
        for line in self.file:
            lineno += 1
            line = line.strip()
            if(line[:1] == '#'): continue
            if(len(line) == 0): continue
            values = line.split(';')
            
            # assign to token class
            tok = Token()
            tok.directions = values[0]
            tok.attack = values[1]
            tok.defense = values[2]
            tok.idno = values[3]
            
            if values[4]:
                tok.desc = values[4]
            
            if not tok.valid():
                raise Exception("Invalid Token at line: {0}".format(lineno))

            if tok.idno in self.tokenSet:
                raise Exception("A Token id is used twice at line: {0}".format(lineno))

            self.tokenSet.add(tok.idno)

            # callback
            func(tok)
            
            
