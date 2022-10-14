#import matplotlib.pyplot as plt
import numpy as np

# for eff map
import glob
import os
import time
import sys
import ROOT
from array import array
import json

from array import array
import math


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


def cdPath(thePath,homePath=os.getcwd()):
	if os.path.exists(thePath):
		os.chdir(thePath)
		if thePath!=homePath:
			print ("folder",thePath,"found!")
	else:
		os.makedirs(thePath)
		os.chdir(thePath)
		print ("folder",thePath,"does not exist, created!")


# if there is/isn't already one at the start/end of the str, add/subtract it
# e.g. changeStr(inDir,"abcde","-","end")
def changeStr(theStr,theTh,howToChange="+",pos="end"):
	theStr_part=""
	if len(theStr)>=len(theTh):
		if "end" in pos:
			idxStart=len(theStr)-len(theTh)
			#if 3 letters, want to check/add 1, will check 2 if count from 0
			idxEnd=len(theStr)
		elif "start" in pos:
			idxStart=0
			idxEnd=len(theTh)
		theStr_part=theStr[idxStart:idxEnd:1]
		#print(theStr_part)

	if "+" in howToChange:
		if theStr_part!=theTh:
			if "end" in pos:
				theStr=theStr+theTh
			elif "start" in pos:
				theStr=theTh+theStr
	if "-" in howToChange:
		if theStr_part==theTh:
			if "start" in pos:
				theStr=theStr[len(theTh):]
			elif "end" in pos:
				theStr=theStr[:len(theStr)-len(theTh)]
	#print(theStr)
	return theStr


def addPath(thePath,fileName):
	fullAddress=""
	thePath=changeStr(thePath,"/","+","end")
	fileName=changeStr(fileName,"/","-","start")
	fullAddress=thePath+fileName
	return fullAddress


def writeList(theList,fPath):
	f=open(fPath,"w")
	for i in range(len(theList)):
		if type(theList[i])==list:
			assembled=""
			for j in range(len(theList[i])):
				assembled=assembled+theList[i][j]+"	"
			assembled=assembled[0:-1,1]
		elif type(theList[i])==str:
			f.write(theList[i])
		else:
			print("in function 'writeList', theList[i] is somehow neither a list nor a string")
	f.close()


# ------ ------ root related ------ ------

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


def root_getOrMkdir (theDir, name):
	dirName = theDir.Get(name)
	if dirName:
		return dirName
	else:
		theDir.mkdir(name)
		dirName=theDir.Get(name)
	return dirName




# returns the h in inF
def root_retHist(inF, dirName, histname):
	#print ("str(histname): ",str(histname))
	#hist = inF.Get(str(histname)).Clone(str(histname))
	print ("dirName+str(histname): ",dirName+str(histname))
	hist = inF.Get(dirName+str(histname)).Clone(dirName+str(histname))
	#infile.Close()
	return hist

# also enters the inFile, and saves in outFile
def get_hist(outFile, inFileName, dirName, histname):
	infile = ROOT.TFile(inFileName,'read')
	outFile.cd()
	print ("dirName+/+str(histname): ",dirName+"/"+str(histname))
	hist = infile.Get(dirName+"/"+str(histname)).Clone(dirName+"/"+str(histname))
	#infile.Close()
	return hist


def write_outputfile(outFileName,dirName,hist, histname):
	#outfile = ROOT.TFile(outFileName,'update')
	theDir = getOrMkdir(outFileName,dirName)
	theDir.WriteTObject(hist,histname)
	#outFileName.Close()


def getWeights(w, target_hist):
	#weights = default_hist.Clone('weights')

	#sum_default = default_hist.GetSumOfWeights()
	#sum_target = target_hist.GetSumOfWeights()

	#nBins_eta = default_hist.GetNbinsY()
	#nBins_pt = default_hist.GetNbinsX()

	#target_clone = target_hist.Clone('target_clone')
	#target_clone.Scale(float(sum_default)/sum_target)

	weights = target_hist.Clone('weights')
	weights2 = target_hist.Clone('weights')
	#sum_target = target_hist.GetSumOfWeights()#total nof events/weights?

	nBins_eta = target_hist.GetNbinsY()
	nBins_pt = target_hist.GetNbinsX()

	target_clone = target_hist.Clone('target_clone')
	#target_clone.Scale(float(w))#how does this work?

	Weight = w
	WeightErr = w

	for ipt in range(1,nBins_pt+1):
		for ieta in range(1,nBins_eta+1):

			'''
			#binContDef = float(default_hist.GetBinContent(ipt,ieta))
			binContTarget = float(target_clone.GetBinContent(ipt,ieta))
			binErrTarget = float(target_clone.GetBinError(ipt,ieta))

			#frac_default = binContDef/float(sum_default)
			Weight = binContTarget*w #float(sum_target)
			#frac_reweight = binContTarget/float(sum_default) #float(sum_target)
			WeightErr = binErrTarget*w
			'''

			'''
			if frac_default < 0.0001 or  frac_reweight < 0.0001:
				Weight = 1
				WeightErr = 0
			else:
				Weight = frac_default/frac_reweight

				### formula for error of (x1*(n2 + x2))/(x2*(n1 + x1)) where the variables are:
				x1 = binContDef
				x2 = binContTarget
				n1 = sum_default - binContDef
				n2 = sum_default - binContTarget

				WeightErr = math.sqrt(x1*(n2+x2)*( n1*(n2+x2)/(n1+x1)+x1*n2/x2 ))/(n1+x1)/x2
			'''

			weights2.SetBinContent(ipt,ieta,Weight)
			weights2.SetBinError(ipt,ieta,WeightErr)

	return weights,weights2


def applyWeights(weights,hist):
	reweighted = hist.Clone(hist.GetName())
	#reweighted = hist.Clone(hist.GetName()+'_reweighted')
	#print ('Made it here')
	nBins_eta = weights.GetNbinsY()
	nBins_pt = weights.GetNbinsX()

	for ipt in range(1,nBins_pt+1):
		for ieta in range(1,nBins_eta+1):
			reweighted.SetBinContent(ipt,ieta,weights.GetBinContent(ipt,ieta)*hist.GetBinContent(ipt,ieta))
			#print (str(weights.GetBinContent(ipt,ieta))+' '+str(hist.GetBinContent(ipt,ieta)))
			errPart1 = (weights.GetBinContent(ipt,ieta)*hist.GetBinError(ipt,ieta))**2
			errPart2 = (weights.GetBinError(ipt,ieta)*hist.GetBinContent(ipt,ieta))**2

			reweighted.SetBinError(ipt,ieta, math.sqrt(errPart1+errPart2))
#			 print ('pt ',reweighted.GetXaxis().GetBinCenter(ipt),' eta ',reweighted.GetYaxis().GetBinCenter(ieta), \
#				 ' before ',hist.GetBinContent(ipt,ieta) ,' reweight ' \
#				 ,reweighted.GetBinContent(ipt,ieta),' err ',reweighted.GetBinError(ipt,ieta))
			if reweighted.GetBinContent(ipt,ieta)!=0:
				ratio = reweighted.GetBinError(ipt,ieta)/reweighted.GetBinContent(ipt,ieta)
				#print (str(hist.GetName())+' '+str(ipt)+' '+str(ieta)+' '+str(ratio))
	return reweighted


def scaleH(w, target_hist, hName):
	target_clone = target_hist.Clone(hName)
	target_clone.Sumw2();
	target_clone.Scale(float(w))
	return target_clone


# dsList may contain unwanted characters or lines
# this func leaves only a list of ds names
def cleanDatasetList(dsList):
	cleanedList=[]
	#Identify the mc files in the sample lists
	for ds in dsList:
		if "#" in ds :
			continue
		if ("mc" not in ds) or (("user." not in ds) and ("NTUP_PILEUP" not in ds)):
			continue
		ds=ds.replace("\n","")
		ds=ds.replace("/","")
		ds=ds.replace(" ","")
		cleanedList.append(ds)
	return cleanedList


def downloadDatasets(dsList):
	for ds in dsList:
		command="rucio download "+ds
		print ("downloading, command:",command)
		os.system(command)
	print ("\n\n")


def mergeDatasets(dsList,mergedFileName):
	command="hadd "+mergedFileName
	for ds in dsList:
		if "NTUP_PILEUP" in ds:
			command=command+" "+ds+"/*.root.1"#extension of NTUP_PILEUP files is .root.1
		else:
			command=command+" "+ds+"/*.root"
	print ("merging the downloaded datasets!\nhaddCommand:",command)
	os.system(command)
	print ("\n\n")


def rebin2D(histtype,hist,ptbinning,etabinning):
    hnew = ROOT.TH2F('rebinned_'+hist.GetName()+'_'+histtype,'rebinned_'+hist.GetName()+'_'+histtype,
        len(ptbinning)-1,array('f',ptbinning),len(etabinning)-1,array('f',etabinning))


    hnew_err = ROOT.TH2F('err','err',len(ptbinning)-1,array('f',ptbinning),len(etabinning)-1,array('f',etabinning))

    xaxis = hist.GetXaxis()
    yaxis = hist.GetYaxis()

    for j in range(1,yaxis.GetNbins()+1):
        for i in range(1,xaxis.GetNbins()+1):

            ptval = xaxis.GetBinCenter(i)
            etaval = yaxis.GetBinCenter(j)

            if hist.GetBinContent(i,j) < 0:
                continue

            if ptbinning[0] <= ptval < ptbinning[-1] and etabinning[0] <= etaval < etabinning[-1]:
                hnew.Fill(ptval,etaval,hist.GetBinContent(i,j))
                hnew_err.Fill(ptval,etaval,hist.GetBinError(i,j)**2)

    for j in range(1,hnew.GetYaxis().GetNbins()+1):
        for i in range(1,hnew.GetXaxis().GetNbins()+1):
            hnew.SetBinError(i,j, math.sqrt(hnew_err.GetBinContent(i,j)) )

    return hnew
