# for eff map
import glob
import os
import time
import sys
import ROOT
from array import array
import json


from ROOT import gStyle
from ROOT import TFile

#import matplotlib.pyplot as plt
import numpy as np

import math
from itertools import product



#==================================
#------ ------ types ------ ------
#==================================

def changeType(theThing,theType):
	if "float" in theType:
		#print('changing to float')
		theThing=float(theThing)
	elif "int" in theType:
		#print('changing to int')
		theThing=int(theThing)
	elif "str" in theType:
		#print('changing to str')
		theThing=str(theThing)
	return theThing


# a function that uses itself and hopefully can change any dimention of list's every element
def changeType_list(theList,theType):
	if type(theList) is list:
		newList=[]
		for i in range(len(theList)):
			newList.append(changeType_list(theList[i],theType))
	else:
		newList=changeType(theList,theType)
	return newList


#==================================
#------ ------ string manipulation ------ ------
#==================================

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


# finds the string between str1 and str2
def findBetween(theStr,str1,str2,toPrint=""):
	i_s=theStr.find(str1)
	theFound=None
	#print("i_s:",i_s)
	if i_s<0 or i_s>=len(theStr):
		#technically only <0 is sufficient
		#i_s will be -1 if str not found
		if toPrint!="":
			print("in func 'findBetween', 1st str '"+str1+"' not found in '"+theStr+"', returning None")
	else:
		str_aft1=theStr[i_s+len(str1):len(theStr):1]
		#print("str_aft1:",str_aft1)
		i_e=str_aft1.find(str2)
		#print("i_e:",i_e)
		if i_e<0 or i_e>=len(str_aft1):
		#technically only <0 is sufficient
			if toPrint!="":
				print("in func 'findBetween', 2nd str '"+str2+"' not found in '"+theStr+"' or is before 1st str, returning None")
		else:
			theFound=str_aft1[0:i_e:1]
	#print("the found string:",theFound)
	return theFound


# go through a list, only leave the part within two lines, 1st contains str1, 2nd contains str2
def cutList(list_all,str1,str2,idx_s=0):
	list_new=[]
	i=idx_s
	while i<len(list_all):
		if str1 in list_all[i]:
			print("found '"+str1+"' at line "+str(i)+"! starting")
			list_new.append(list_all[i])
			j=i+1
			while j<len(list_all):
				list_new.append(list_all[j])
				if str2 in list_all[j]:
					print("found '"+str2+"' at line "+str(j)+"!")
					j=len(list_all)
					i=j
				else:
					j=j+1
		else:
			i=i+1
	#print("list_new:",list_new)
	return list_new


#"starts" and "ends" are both a list of lists
def fillTable(starts, ends, allLines, theList, sep="	"):
	if len(starts)!=len(ends):
		print("in fillList, the starts and ends have different lengths, please make sure that their lengths are the same")
		return theList
	for i in range(len(starts)):
		for aLine in allLines:#could make this more efficient by noting down this index and i starts from that (if sure that the legends have the same order as the info shows up in allLines)
			theInfo=findBetween(aLine,starts[i][0],ends[i][0])
			#print("theInfo:",theInfo)
			if theInfo!=None:
				if i<len(theList):
					theList[i].append(sep)
					theList[i].append(theInfo)
				else:
					theList.append([theInfo])
	print("table filled!")
	return theList


def addLineBreak_list(theList):
	for i in range(len(theList)):
		if len(theList[i])!=0 and theList[i][-1]=="\n":
			pass
		else:
			if type(theList[i])==list:
				theList[i].append("\n")
			elif type(theList[i])==str:
				theList[i]=theList[i]+"\n"
	return theList


#==================================
#------ ------ lists ------ ------
#==================================

# an n-dimensional str list, return 1D list with all elements attached combinatorially
# e.g. list1=[[a],[b,c],[d]]
# return [abd,acd]
def multiplyList(inF_paths):
	h_paths=inF_paths[0]
	for i in range(1, len(inF_paths)):
		h_paths=list(product(h_paths,inF_paths[i]))
		for j in range(len(h_paths)):
			h_paths[j]=h_paths[j][0]+h_paths[j][1]
			#print(h_paths[j])
		#h_paths=list(map(add, h_paths, inF_paths[i]) )
		#print("iteration",i,h_paths)
	return h_paths


def copyList(theList):
	newList=[]
	for i in range(len(theList)):
		newList.append(theList[i])
	return newList


#==================================
#------ ------ files ------ ------
#==================================

def cdPath(thePath,homePath=os.getcwd()):
	if os.path.exists(thePath):
		os.chdir(thePath)
		if thePath!=homePath:
			print ("folder",thePath,"found!")
	else:
		os.makedirs(thePath)
		os.chdir(thePath)
		print ("folder",thePath,"does not exist, created!")


def addPath(thePath,fileName):
	fullAddress=""
	thePath=changeStr(thePath,"/","+","end")
	fileName=changeStr(fileName,"/","-","start")
	fullAddress=thePath+fileName
	return fullAddress


# write a 2D list to file (the elements in the 1st layer can be either string or list)
def saveList(theList,f,sep='	',fileOpt='w'):
	#print(type(f))#<class '_io.TextIOWrapper'>
	if type(f) is str:
		print('saving in file',f)
		f = open(f, fileOpt)
	#print('the type of theList =',type(theList))
	if type(theList) is str:
		f.write(theList)
	else:
		for i in range(len(theList)):
			#print('type of list elements =',type(theList[i]),theList[i])
			if type(theList[i])==list:
				#print('theList[i] =',theList[i])
				saveList(theList[i],f,sep)
				f.write('\n')
			elif type(theList[i])==str:
				#print("wrote str"+theList[i])
				f.write(theList[i])
				if i!=len(theList)-1:
					f.write(sep)
			elif type(theList[i])==None:
				#print("in function 'saveList', theList[i] is None")
				f.write("")
			#else:
			#	print("in function 'saveList', theList[i] is somehow neither a list nor a string")

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


def print2D(f_inF,ouDir,h_paths,h_names,rebX,rebY):
	c = ROOT.TCanvas('c','c',1000,750)
	for i in range(len(h_paths)):
		h=f_inF.Get(h_paths[i]);
		if h==None:
			print("hist "+h_paths[i]+" doesn't exist")
		else:
			#print(h.GetName())
			h.Rebin2D(rebX,rebY);
			h.Draw("colz")
			c.SaveAs(ouDir+h_names[i]+".pdf");


def fitGaus(h):
	h.Print()
	h.Fit("gaus")


def getTH1s(f_inF,ouDir,h_paths,h_names,rebX=1):
	h_li=[]
	for i in range(len(h_paths)):
		h=f_inF.Get(h_paths[i]);
		gStyle.SetOptStat(11)
		#h.GetYaxis().SetRange(0,100);
		#h.SetAxisRange(0., 1e8,"Y");
		h.Print()
		print("integral:",h.Integral())
		if rebX!=1:
			h.Rebin(rebX);
			#print("after rebin")
		h_li.append(h)
	return h_li


def printTH1s(h_li,ouDir,h_names):
	c = ROOT.TCanvas('c','c',1000,750)
	gStyle.SetOptStat(11)
	for i in range(len(h_li)):
		h=h_li[i]
		#h=getTH1(f_inF,ouDir,h_paths,h_names,rebX)
		#h.Print()
		h.Draw("")
		c.SaveAs(ouDir+h_names[i]+".pdf");

