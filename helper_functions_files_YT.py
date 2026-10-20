import os
import shutil
import re
import numpy as np

from code.helperFunctions_Yusong import changeStr

def cd_path(thePath, homePath=os.getcwd()):
	if os.path.exists(thePath):
		os.chdir(thePath)
		if thePath!=homePath:
			print ("folder",thePath,"found!")
	else:
		os.makedirs(thePath)
		os.chdir(thePath)
		print ("folder",thePath,"does not exist, created!")


def add_path(thePath,fN):
	fullAddress=""
	thePath=changeStr(thePath,"/","+","end")
	fN=changeStr(fN,"/","-","start")
	fullAddress=thePath+fN
	return fullAddress


# orders files in dir_path according to the last number
#in the file name
# can have maximum 1 file in dir_path that
#does not have any numbers in file name

def order_files(dir_path, selection_rule, startn=1, pr=1):
	# Finds all files in the specified directory that match the selection rule
	files = [f for f in os.listdir(dir_path) if os.path.isfile(os.path.join(dir_path, f)) and selection_rule in f]
	
	# Sorts the files
	files.sort() #file names ordered differently before and after .sort()

	page_num=[]
	for fN in files:
		nums=re.findall(r'\d+\.\d+|\d+', fN)
		if len(nums)==0:
			page_num.append(0)
		else:
			page_num.append(float(nums[-1]))
	
	#list1 = [3, 2, 4, 1]
	#list2 = ['three', 'two', 'four', 'one']

	# Get sorting indices
	indices = np.argsort(page_num)
	
	# Apply indices to both lists
	#sorted_list1 = np.array(page_num)[indices].tolist()
	# list of file names in the correct order
	sorted_list2 = np.array(files)[indices].tolist()
	
	#print(sorted_list1) # Output: [1, 2, 3, 4]
	sorted_list2=sorted_list2[startn-1:len(sorted_list2)]
	if pr:	
		print('new order of files: ')
		print(sorted_list2) # Output: ['one', 'two', 'three', 'four']
	
	return sorted_list2



def find_hidden_files(fNs_ord, debug_l=1):
	# find hidden files
	fNs_hidden=[]
	for fN in fNs_ord:
		if fN[0]==".":
			fNs_hidden.append(fN)
	if debug_l>=1:
		print("hidden files:",fNs_hidden)
	return fNs_hidden


def rename_1_file(file_path_i, file_path_f):
	print('Changing file "'+file_path_i+"' to '"+file_path_f+"'")
	# Copy the file metadata
	#shutil.copystat(file_path_i, file_path_f)
	#shutil.copy2(file_path_i, file_path_f)
	# Rename the file
	if file_path_i!=file_path_f:
		os.rename(file_path_i, file_path_f)
	else:
		print("old name and new name same, no need for renaming")
	return 0


# given lists of initial file names and new file names,
# change old files to their corresponding new names
# has NO overwrite prevention!
def rename_list_of_files(fNs_i, fNs_f, dir_path='', fNs_all=[], arg_overwrite="append", arg_exec=0):
	#print('------ ------ preparing to change names of files...')
	cd_path(dir_path)
	print("initial ",len(fNs_i)," files:",fNs_i)
	print("new names of",len(fNs_f),"files:",fNs_f)
	#fNs_i,fNs_f=overwrite_prevention(fNs_i, fNs_f, fNs_all, arg_overwrite)
	if arg_exec:
		for fN_i, fN_f in zip(fNs_i, fNs_f):
			rename_1_file(fN_i, fN_f)
	else:
		print("\nfile names not changed\n")
	return 0


def add_appendix_to_file_name(fN, to_add):
	fN_new=""
	if fN.find(".")>=0:
		f_name_main=fN.split(".")[0]
		f_name_format=fN.split(".")[-1]
		fN_new=f_name_main+to_add+"."+f_name_format
	return fN_new


def find_clashing_elements(l1, l2, debug_l=0):
	debug_l0=6
	clash_exists=0
	#print("!!!!!!\nl1: ",l1,"\n\nl2: ",l2,"\n")

	fNs_clash=set(l1) & set(l2)
	if not fNs_clash:
		if debug_l>=debug_l0: print("no clashing names!")
	else:
		if debug_l>=debug_l0: print("some file names already exist in the target directory")
		clash_exists=1
	return fNs_clash, clash_exists


def increment_suffix(fN_clash, fNs_all, max_try="10"):
	#print("finding a new name for clashing file name",fN_clash,"...")
	fN_new=fN_clash
	for i_suffix in range(1, max_try+1):
		if fN_new in fNs_all:
			fN_new=add_appendix_to_file_name(fN_clash, "-"+str(i_suffix))
			continue
		else:
			if i_suffix==max_try:
				print("!!! !!! PAY ATTENTION: when incrementing suffix of file, max try of",max_try,"reached!")
			return fN_new


# only works for already ordered fNs_f
def renumber_fNs(fNs_i, fNs_f, arg_exec=0):
	print("initial ",len(fNs_i)," files:",fNs_i)
	print("new names of",len(fNs_f),"files:",fNs_f)
	fNs_i.reverse()
	fNs_f.reverse()

	temp_pre='tmp_10086_'
	overlapped_i=[]
	overlapped_f=[]
	i=0

	for file_path_i, file_path_f in zip(fNs_i, fNs_f):
		if (file_path_f not in fNs_i[(i+1):len(fNs_i)]):
			if arg_exec: rename_1_file(file_path_i, file_path_f)
		else:
			print('Changing file "'+file_path_i+"' to '"+file_path_f+"', but... creating tmp file")
			#print(i,len(fNs_i),fNs_i[i:len(fNs_i)])
			tempN=temp_pre+file_path_f
			if arg_exec: rename_1_file(file_path_i, tempN)
			#time.sleep(1)
			overlapped_i.append(tempN)
			overlapped_f.append(file_path_f)
		i=i+1
		
	if len(overlapped_i)!=0:
		#print(overlapped_i)
		#print(overlapped_f)
		for oldN, newN in zip(overlapped_i, overlapped_f):
			if arg_exec: rename_1_file(oldN, newN)
	fNs_i.reverse()
	fNs_f.reverse()

	return fNs_i, fNs_f


# to avoid over-writing files, modify new file name
# arg_rename options: "reorder" - do not overwrite, last number +1
#        "append" - do not overwrite, append a number
#        "renumber" - redo numbering and execute rename
#        "overwrite"
def overwrite_prevention(fNs_i, fNs_f, fNs_all=[], arg_overwrite="append", arg_exec=0):
	# check if has clashing names
	print("checking for clashing names!")
	fNs_clash, clash_exists=find_clashing_elements(fNs_f, fNs_all, 6)
	#if fNs_all==[]:
	#	print("list of all file names empty, obtaining all files in current path")
	#	fNs_all=os.listdir(path_current)
	#print("in overwrite_prevention, number of initial files\n",len(fNs_i), "\nnumber of final files\n", len(fNs_f),"\n")

	if clash_exists:
		print("clashing names:",fNs_clash)
		if arg_overwrite=="overwrite":
			return fNs_i, fNs_f
		elif arg_overwrite.find("append")>=0:
			path_current=os.getcwd()
			max_appendix=10
			if clash_exists: 
				for fN_clash in fNs_clash:
					fN_new=increment_suffix(fN_clash, fNs_all, max_appendix)
					if fN_new in fNs_f: fN_new=increment_suffix(fN_new, fNs_f, max_appendix)
					fNs_f[fNs_f.index(fN_clash)]=fN_new
			print("new initial and final names:")
			print("initial:",fNs_i)
			print("final:",fNs_f,"\n")
		elif arg_overwrite.find("renumber")>=0:
			pass
		#	print("warning: clash prevention (renumber option) does not work yet if final names are not ordered already! your file might be overwritten") # this would never happen for existing way of generating fNs_f in rename_files
		#	fNs_i, fNs_f = renumber_fNs(fNs_i, fNs_f, arg_exec)
		else: 
			print("arg_overwrite must contain 'append', 'renumber', or 'overwrite'!")

	return fNs_i, fNs_f


# renames the files according to the naming rule
# uses overwrite_prevention and rename_list_of_files
def rename_files(fNs, naming_rule, dir_path="", start_n=1, arg_exec=0, arg_overwrite="append"):
	cd_path(dir_path)
	print("overwrite option:", arg_overwrite)
	fNs_i=[]
	fNs_f=[]
	for i, fN in enumerate(fNs, start_n):
		#print(i, fN)
		# use format to insert numbers (if desired) in the new name
		new_file_name = naming_rule.format(i)
		fNs_i.append(fN)
		fNs_f.append(new_file_name)

	print('found',len(fNs_i),'initial file names:',fNs_i,"\n")
	print('created',len(fNs_f),'new file names:',fNs_f,"\n")

	if arg_overwrite.find("renumber")>=0:
		fNs_i, fNs_f = renumber_fNs(fNs_i, fNs_f, arg_exec)
		return fNs_f

	fNs_i, fNs_f = overwrite_prevention(fNs_i, fNs_f, fNs, arg_overwrite, arg_exec)
	if arg_overwrite.find("renumber")<0:
		rename_list_of_files(fNs_i, fNs_f, dir_path, fNs, arg_overwrite, arg_exec)

	return fNs_f


def remove_files(f_to_rm, inD="", arg_exec=0, debug_l=1):
	#print("removing files")
	deb=6
	if arg_exec==0:
		if debug_l>deb: print("did not remove files")
		return 0

	for fN in f_to_rm:
		f_rm_path=add_path(inD, fN) 
		#print(f_rm_path)
		if os.path.exists(f_rm_path):
			os.remove(f_rm_path)
			print(f_rm_path,"is removed from",inD)
	return 1
