import matplotlib.pyplot as plt
import numpy as np

def getData(fileName):
	theFile= open(fileName,"r")
	lines=theFile.readlines()
	#print lines
	lines2=[]
	for aLine in lines:
		aLine=aLine.replace("\n","")
		splittedLine=aLine.split("\t")
		lines2.append(splittedLine)
	#print lines2
	return lines2

def getXY(the2Dlist,xName,yName):
	X=[]
	Y=[]
	return X,Y


def changeType(theThing,theType):
	if "float" in theType:
		theThing=float(theThing)
	elif "int" in theType:
		theThing=int(theThing)
	elif "str" in theType:
		theThing=str(theThing)
	return theThing


def listChangeItemType(theList,theType):
	#theList=[["1","2"],[["3","4"],"5"]]
	#print "theList",theList,type(theList)
	#listDimension=0
	#newList=theList
	if type(theList)==list:
		for i in range(len(theList)):
			#while type(newList)==list:
			#	newList=newList[0]
			#	listDimension+=1
			#	print "islist!"
			theList[i]=changeType(theList[i],theType)
	else:
		theList=changeType(theList,theType)
	#print "theList",theList,type(theList)
	return theList
	

def changeFile(theFile,toSearch,changeTo)
	print(theFile)

