
int DEBUG=2;


//==================================
//------ ------ string ------ ------
//==================================

std::string findBetween(std::string theStr, std::string str1, std::string str2){
	int idx1=theStr.find(str1);
	int idx2=theStr.find(str2);
	std::string foundStr="";
	for (int i=idx1+str1.size();i<idx2;i++){
		foundStr=foundStr+theStr[i];
	}
	return foundStr;
}

void printString(std::string theString, std::string anotherString=""){
	//std::cout<<"function started!\n";
	if (theString!=""){
		std::cout<<theString<<anotherString;
	}
	//std::cout<<"function ended!\n";
}


// takes a float and the desired nof digit
// return str
std::string roundToStr(float theNum, int nofDigit){
	std::stringstream strStream;
	strStream << std::fixed << std::setprecision(nofDigit) << theNum;
	std::string s = strStream.str();
	return s;
}


//==================================
//------ ------ vector ------ ------
//==================================

//prints 1D vector in std::string
//printVector(theDataPoints[0],"vector theDataPoints[0]: \n");
void printVector(std::vector<std::string> theVector, std::string theString=""){
	printString(theString);
	int i=0;
	int NtheVector=theVector.size();
	//std::cout<<NtheVector<<"\n";
	if (NtheVector>1){
		for (i;i<NtheVector-1;i++){
			std::cout<<theVector[i]<<"    ";
		}
	}
	if (NtheVector>0){
		std::cout<<theVector[NtheVector-1]<<"\n";
	}else if (NtheVector==0){
		std::cout<<"in printVector (string), the vector you're trying to print has length 0!\n";
	}
}


void printVector(std::vector<TString> theVector, std::string theString=""){
	printString(theString);
	int i=0;
	int NtheVector=theVector.size();
	//std::cout<<NtheVector<<"\n";
	if (NtheVector>1){
		for (i;i<NtheVector-1;i++){
			std::cout<<theVector[i]<<"    ";
		}
	}
	if (NtheVector>0){
		std::cout<<theVector[NtheVector-1]<<"\n";
	}else if (NtheVector==0){
		std::cout<<"in printVector (string), the vector you're trying to print has length 0!\n";
	}
}


// prints 1D vector in double
void printVector(std::vector<double> theVector, std::string theString="", std::string theSep="    "){
	printString(theString);
	int i=0;
	int NtheVector=theVector.size();
	//std::cout<<NtheVector<<"\n";
	if (NtheVector>1){
		for (i;i<NtheVector-1;i++){
			std::cout<<theVector[i]<<theSep;
		}
	}
	if (NtheVector>0){
		std::cout<<theVector[NtheVector-1]<<"\n";
	}else if (NtheVector==0){
		std::cout<<"in printVector (double), the vector you're trying to print has length 0!\n";
	}
}


// prints 1D vector in int
void printVector(std::vector<int> theVector, std::string theString=""){
	printString(theString);
	int i=0;
	int NtheVector=theVector.size();
	//std::cout<<NtheVector<<"\n";
	if (NtheVector>1){
		for (i;i<NtheVector-1;i++){
			std::cout<<theVector[i]<<"    ";
		}
	}
	if (NtheVector>0){
		std::cout<<theVector[NtheVector-1]<<"\n";
	}else if (NtheVector==0){
		std::cout<<"in printVector (double), the vector you're trying to print has length 0!\n";
	}
}


// prints 2D vector in std::string, used in getData
// uses printVector
//printVector(theDataPoints[0],"vector theDataPoints[0]: \n");
void printVectorVector(std::vector<std::vector<std::string>> theVector, std::string theString=""){
	printString(theString);
	int i=0;
	int NtheVector=theVector.size();
	//std::cout<<"has "<<NtheVector<<" elements\n";
	if (NtheVector>1){
		for (i;i<NtheVector-1;i++){
			printVector(theVector[i]);
		}
	}
	if (NtheVector>0){
		printVector(theVector[NtheVector-1]);
		std::cout<<"\n";
	}else if (NtheVector==0){
		std::cout<<"has length 0!\n";
	}
}


//converts an array to a vector
std::vector<double> array_vector(double* theArray){
	std::vector<double> theVec;
	int N=sizeof(*theArray)/sizeof(theArray[0]);
	std::cout<<"the size of the array N="<<N<<"\n";
	for (int i=0; i<N; i++){
		theVec.push_back(theArray[i]);
	}
	return theVec;
}


int maxSize(std::vector<std::vector<std::string>> theVec,std::string toPrint=""){
	int maxS=0;
	for (int i=0;i<theVec.size();i++){
		if (theVec[i].size()>maxS){maxS=theVec[i].size();}
	}
	if (toPrint!=""){std::cout<<toPrint<<"the maximum size of the elements in this vector: "<<maxS<<"\n";}
	return maxS;
}


// transpose a 2D vec with type std::string
// works for uneven nof elements too, will make the transposed vector even by adding ""
std::vector<std::vector<std::string>> transposeVec(std::vector<std::vector<std::string>> theVec){
	int maxS=maxSize(theVec,"! ");
	std::vector<std::vector<std::string>> transposed={};
	for (int i=0;i<theVec.size();i++){
		for (int j=0;j<maxS;j++){
			if (j>=transposed.size()){
				transposed.push_back({});
			}
			if (j<theVec[i].size()){
				transposed[j].push_back(theVec[i][j]);
			}else{
				transposed[j].push_back("");
			}
		}
	}
	return transposed;
}


void printVdep(std::vector<std::vector<double>> allVdeps, int howMany=2){
	std::vector<double> Vdep1;
	std::vector<double> Vdep1_unc;
	std::vector<double> Vdep2;
	std::vector<double> Vdep2_unc;
	//std::cout<<"allVdeps.size(): "<<allVdeps.size()<<"\n";
	if(allVdeps.size()>0){
		for (int i=0;i<allVdeps.size();i++){
			if (i%howMany==0){
				Vdep1.push_back(allVdeps[i][3]);
				Vdep1_unc.push_back(allVdeps[i][4]);
			}else if(i%howMany==1){
				Vdep2.push_back(allVdeps[i][3]);
				Vdep2_unc.push_back(allVdeps[i][4]);
			}else{
				std::cout<<"this case should not happen :|";
			}
		}
	}
	printVector(Vdep1,"1st Vdep: ",", ");
	printVector(Vdep1_unc,"1st Vdep unc: ",", ");
	printVector(Vdep2,"2nd Vdep: ",", ");
	printVector(Vdep2_unc,"2nd Vdep unc: ",", ");
}


// finds a string element in an string vector
int findItemInVector(std::vector<std::string> theVector, std::string strToFind){
	//std::cout<<"This is the findItemInVector for string! Finding string \""<<strToFind<<"\"\n";
	int indexOfElement=-1; int i=0;
	for (i;i<theVector.size();i++){
		//std::cout<<"in for loop, i: "<<i<<"\n";
		if (theVector[i]==strToFind){
			//std::cout<<"in if, theVector[i]: "<<theVector[i]<<"\n";
			indexOfElement=i;
			break;
		}
	}
	//std::cout<<"Exiting findItemInVector, indexOfElement: "<<indexOfElement<<", the string looking for: "<<strToFind<<", i: "<<i<<"\n";
	return indexOfElement;
}


int findItemInVector(std::vector<TString> theVector, std::string strToFind){
	//std::cout<<"This is the findItemInVector for TString!\n";
	int indexOfElement=-1; int i=0;
	for (i;i<theVector.size();i++){
		if (theVector[i]==strToFind){
			indexOfElement=i;
			break;
		}
	}
	//std::cout<<indexOfElement<<": "<<strToFind<<" <- indexOfElement, i: "<<i<<"\n";
	return indexOfElement;
}


std::vector<double> expandVector(std::vector<double> &theVector, int theSize, int whichToRepeat=0, std::string toPrint=""){
	//std::cout<<"in expandVector! Size of vector to expand: "<<theVector.size()<<"\n";
	printString(toPrint);

	if (theVector.size()==0){
		std::cout<<"the vector is empty, can't be expanded!\n";
	}else if(theVector.size()<theSize){
		//std::cout<<"number of items in vector: "<<theVector.size()<<", smaller than specified, expanding it to "<<theSize<<"!\n";
		for(int j=theVector.size();j<theSize;j++){
			theVector.push_back(theVector[whichToRepeat]);
		}		
	}else{
		std::cout<<"the vector already has the same number of or more elements than "<<theSize<<"! Will not do anything to expand it!\n";
	}
	//std::cout<<"size of vector after expanded: "<<theVector.size()<<"\n";
	//printVector(theVector);
	if(toPrint!=""){
		printVector(theVector);
	}
	return theVector;
}


std::vector<std::vector<int>> expandVector(std::vector<std::vector<int>> &theVector, int theSize, int whichToRepeat=0, std::string toPrint=""){
	printString(toPrint);
	if (theVector.size()==0){
		std::cout<<"the vector is empty, can't be expanded!\n";
	}else if(theVector.size()<theSize){
		for(int j=theVector.size();j<theSize;j++){
			theVector.push_back(theVector[whichToRepeat]);
		}		
	}else{
		std::cout<<"the vector already has the same number of or more elements than "<<theSize<<"! Will not do anything to expand it!\n";
	}
	//if(toPrint!=""){
	//	printVectorVector(theVector);
	//}
	return theVector;
}


//cycle a vector, e.g. in case a list of colours is shorter than the number of files to plot
int cycVec(std::vector<int> theVec, int idx){
	int ret;
	//std::cout<<"theVec.size(): "<<theVec.size()<<" idx: "<<idx<<"\n";
	//printVector(theVec);
	if(theVec.size()<=0){//if vec empty
		//std::cout<<"trying to use a vector, but the vector is empty\n";
		ret=-1;
	}else if(idx<theVec.size()){
		//std::cout<<"idx: "<<idx<<"\n";
		ret=theVec[idx];
	}else if(idx>=theVec.size()){
		int newIdx=idx%theVec.size();
		//std::cout<<"newIdx: "<<newIdx<<"\n";
		ret=theVec[newIdx];
	}
	//std::cout<<"ret: "<<ret<<"\n";
	return ret;
}


double findMinMaxAvg(std::vector<double> theVector, std::string theString=""){
	//std::cout<<"in findMinMaxAvg!\n";
	int NtheVector=theVector.size();
	//std::cout<<NtheVector<<"\n";
	double theValue=-999.;
	if (NtheVector>0){
		theValue=theVector[0];
		if (theString=="max"){
			for (int i=0;i<NtheVector;i++){
				if(theVector[i]>theValue){theValue=theVector[i];}
			}
		}else if (theString=="min"){
			for (int i=0;i<NtheVector;i++){
				if(theVector[i]<theValue){theValue=theVector[i];}
			}
		}else if (theString=="avg"){
			double theSum=0.;
			for (int i=0;i<NtheVector;i++){
				theSum=theSum+theVector[i];
			}
			theValue=theSum/NtheVector;
		}
	}else if (NtheVector==0){
		std::cout<<"has length 0!\n";
	}
	return theValue;
}


//=================================
//------ ------ files ------ ------
//=================================

bool fileExistsOrNot(TString fileName, TString inputPath = ""){
	bool existOrNot;
	std::ifstream ifile;
	std::cout<<inputPath<<fileName<<" ";
	ifile.open(inputPath+fileName);
	if(ifile) {
		existOrNot=true;
		std::cout<<"file exists\n";
	} else {
		existOrNot=false;
		std::cout<<"file doesn't exist\n";
	}
	/*
	TFile* f = TFile::Open(fileName,"f"); 
	if(!f || f->IsZombie()){ 
		std::cout << "Failed to load file" <<fileName<<"\n"; 
		return; 
	}
	*/
	return existOrNot;
}


std::string addPath(std::string folderName, std::string fileName){
	std::string fileFullPath=folderName+fileName;
	fileExistsOrNot(fileFullPath);
	return fileFullPath;
}


std::vector<std::string> addPaths(std::string folderName, std::vector<std::string> fileNames){
	for (int i=0;i<fileNames.size();i++){
		fileNames[i]=addPath(folderName,fileNames[i]);
	}
	return fileNames;
}

std::vector<std::string> addPaths(std::vector<std::string> folderNames, std::vector<std::string> fileNames){
	for (int i=0;i<fileNames.size();i++){
		fileNames[i]=addPath(folderNames[i],fileNames[i]);
	}
	return fileNames;
}

// save 2D vector of std::string in .txt
void saveTxt(std::vector<std::vector<std::string>> &input, std::string outFileName){
	fstream file_out; 
	file_out.open(outFileName+".txt",fstream::out);

	int getArrayLength = input.size();

	for(int i=0; i<getArrayLength; i++){
		for(int j=0; j<input[i].size(); j++){
			file_out << input[i][j] << "\t";
		}
	file_out<<std::endl;
	}
	file_out.close();
}


//================================
//------ ------ data ------ ------
//================================

std::vector<std::string> separateLine(std::string theLine, std::string separateBy,std::string toPrint=""){
	std::vector<std::string> theVector;
	//std::cout<<theLine<<"\n";
	std::string anItem="";
	for (int i=0;i<theLine.size();i++){
		if (theLine[i]!=separateBy){
			anItem=anItem+theLine[i];
		}else{
			theVector.push_back(anItem);
			anItem="";
		}
		if(i==theLine.size()-1){
			theVector.push_back(anItem);
		}
	}
	return theVector;
}


// takes name of a file, gives a vector of vector of strings with file content
// uses func separateLine(,)
std::vector<std::vector<std::string>> getData(std::string fileName, std::string toPrint=""){
	std::vector<std::vector<std::string>> allTests;//each element is a row in the file
	std::cout<<"Reading data from file \""<<fileName<<"\"\n";
	ifstream inTxtFile;
	inTxtFile.open(fileName);
	std::string aLine;
	while (getline (inTxtFile, aLine)) {
		std::vector<std::string> theVector=separateLine(aLine,"\t",toPrint);//each element is a data point in the row
		allTests.push_back(theVector);//push the row to the overall vector
	}
	inTxtFile.close();
	if (toPrint!=""){
		std::cout<<toPrint;
		printVectorVector(allTests);
	}
	return allTests;
}


// takes the resulting 2D vector "allTests" from getData
// puts the particular column (from certain row, take one element from each element (which is a vector) of allTests) in a vector
// when counting the column and row numbers, count from 0
std::vector<double> getData_vector(std::vector<std::vector<std::string>> &theData, int nthColumn, int labelsRow=-1, double offset=0., double factor=1., int selCriteriaColumn=-1, double selCriteria=-999){
	std::vector<double> theVector;
	//printVectorVector(theData);
	for(int i=labelsRow+1;i<(theData.size());i++){
		double theNumber=atof((theData[i][nthColumn]).c_str());
		theVector.push_back((theNumber+offset)*factor);
	}
	//printVector(theVector,"the data vector:\n");
	if (selCriteriaColumn!=-1){
		for(int i=theVector.size()-1;i>=0;i--){
			if(atof((theData[i+labelsRow+1][selCriteriaColumn]).c_str())!=selCriteria){
				theVector.erase(std::next(theVector.begin(),i));
			}
		}
	}
	//printVector(theVector,"the data vector after selection:\n");
	return theVector;
}


std::vector<std::string> get1row(std::vector<std::vector<std::string>> &theData, int nthColumn, int labelsRow=-1){
	std::vector<std::string> theVector;
	//printVectorVector(theData);
	for(int i=labelsRow+1;i<(theData.size());i++){
		std::string theInfo=(theData[i][nthColumn]).c_str();
		theVector.push_back(theInfo);
	}
	//printVector(theVector,"the data vector:\n");
	return theVector;
}





//======================================
//------ ------ root files ------ ------
//======================================
// ftag

//https://root-forum.cern.ch/t/list-of-all-histograms-in-a-file/4410/3
//void getAllObjs(TDirectory* f){
std::vector<TString> getAllObjs(TDirectory* f){
	std::vector<TString> objNames;
	f->cd(); 
	f->ls();
	std::cout<<"GetListOfKeys in "<<f->GetTitle()<<":\n";
	TIter next(gDirectory->GetListOfKeys());
	int nhist=0;
	TObject* aKey;
	// must have parentheses warning: using the result of an assignment as a condition without parentheses
	while ((aKey = next.Next())) {
		nhist++;
		cout << "Key " << nhist << " ";
		cout << " Classname " <<aKey->GetName() << " ";
		cout << " Title " <<aKey->GetTitle() << endl;
		objNames.push_back(aKey->GetName());
	}
	return objNames;
}


/*
int getNofEvents(TString fileName, TString pathName, TString branchName){
	std::cout<<"f\n";
	TFile* f = TFile::Open(fileName,"f");
	std::cout<<"d\n";
	TDirectory* d = (TDirectory*)f->Get(pathName);
	std::cout<<"h\n";
	//int n=(d->Get(branchName))->GetEntries();
	TH1F* h=(TH1F*) d->Get(branchName);
	std::cout<<"n\n";
	//int n=((TH1F*) d->Get(branchName))->GetEntries();
	int n=h->GetEntries();
	return n;
}
*/


/*
void applyWeight(TString fileName, TString pathName, TString branchName, float w){
	std::cout<<"file: "<<fileName<<" "<<pathName<<" "<<branchName<<"\n";
	TH2F* h=new TH2F();
	TFile* f = TFile::Open(fileName,"UPDATE");
	std::cout<<"d\n";
	TDirectory* d = (TDirectory*)f->Get(pathName);
	std::cout<<"h\n";
	//int n=(d->Get(branchName))->GetEntries();
	h=(TH2F*) d->Get(branchName);
	std::cout<<"n\n";
	//int n=((TH1F*) d->Get(branchName))->GetEntries();
	int n=h->GetEntries();
	std::cout<<"n: "<<n<<"\n";
	int ni=h->Integral();
	std::cout<<"ni: "<<ni<<"\n";
	//TH2F* hnew=h->Scale(w);
	TH2F* h_2=h->Scale(1/1000);
	int n2=h->GetEntries();
	std::cout<<"n2: "<<n2<<"\n";
	ni=h->Integral();
	std::cout<<"ni: "<<ni<<"\n";
	f->Close();

	TFile* f_new = TFile::Open("weighted.root","RECREATE");
	h_2->Write();
	f_new->Close();
}
*/


//================================
//------ ------ plot ------ ------
//================================

class TGE{
	public:
	TGraphErrors* TGE_ptr;
	int colour=8;
	float markerSize=1;
	int markerStyle=8;
	int lineWidth=2;
	TString legend="";
	TString drawOption="lp";

	int indexRow=-1;
	int indexColX=-1;
	int indexColY=-1;
	int indexColXunc=-1;
	int indexColYunc=-1;
	double offsetX=0.;
	double offsetY=0.;
	double factorX=1.;
	double factorY=1.;

	double minX=-999;
	double maxX=-999;
	double minY=-999;
	double maxY=-999;
	int whichTPad=1;
	double minXval;
	double maxXval;
	double minYval;
	double maxYval;
	std::string notes="";
	std::vector<int> fitPoints;

	void setValues(int theColour, float theMarkerSize, int theMarkerStyle, std::string theLegend){
		colour=theColour; 
		markerSize=theMarkerSize;
		markerStyle=theMarkerStyle;
		legend=theLegend;
	}
};


//takes a 2D vector of doubles, ideally of size 4
//Xvec, Yvec, Xunc, Yunc
//and TGE
//make the TGE from data vec, and set the options
TGraphErrors* makeTGraphErrors(std::vector<std::vector<double>> theDataVec, TGE theOptions){
	TGraphErrors* theTGraphErrors=new TGraphErrors;
	int theNthPoint=0;
	//std::cout<<"have "<<theDataVec[0].size()<<"points!\n";
	if(theDataVec.size()==4){//with error bar
		//std::cout<<"vector size correct (4, include uncertainty)!\n";
		//the TMath::Abs should not be needed
		for (int i=0;i<theDataVec[0].size();i++){
			theTGraphErrors->SetPoint(theNthPoint,theDataVec[0][i],theDataVec[1][i]);
			theTGraphErrors->SetPointError(theNthPoint, TMath::Abs(theDataVec[2][i]), TMath::Abs(theDataVec[3][i]));
			theNthPoint=theNthPoint+1;
		}
	}else{//no error bar
		std::cout<<"no uncertainty!\n";
		for (int i=0;i<theDataVec[0].size();i++){
			theTGraphErrors->SetPoint(theNthPoint,theDataVec[0][i],theDataVec[1][i]);
			theNthPoint=theNthPoint+1;
		}
	}
	theTGraphErrors->SetMarkerColor(theOptions.colour);
	//theTGraphErrors->SetMarkerColorAlpha(theOptions.colour, 0.7);//colour transparency
	theTGraphErrors->SetMarkerSize(theOptions.markerSize);
	theTGraphErrors->SetLineColor(theOptions.colour);
	theTGraphErrors->SetLineWidth(theOptions.lineWidth);
	theTGraphErrors->SetMarkerStyle(theOptions.markerStyle);
	return theTGraphErrors;
}


// functions that use canOptions must be written below this class definition of canOptions
class canOptions{
	public:
	TString title="canvas title";
	TString Xaxis="X";
	TString Yaxis="Y";
	int width=900;
	int height=600;
	std::vector<TPad*> TPads;//std::cout<<"nof TPads on can: "<<canOpts.TPads.size()<<"\n"; would output 0

	std::string inputFolder="";
	std::string outputFolder="";
	std::vector<std::string> fileNames={""};//input files that contains data
	std::vector<std::string> legendEntries={""};//list of names of all legends
	std::vector<std::vector<std::vector<std::string>>> data_allFiles;
	TLegend* legend=new TLegend(0.72,0.05,1.0,0.95);//(0.75,0.,1,1.);//(0.72,0.1,0.98,0.9);
	std::vector<TGE> TGEs;//all TGraphErrors and their options
	std::vector<TLine*> TLines;
	std::vector<TGraphAsymmErrors*> TGAEs;

	std::string figFileName="figFileName";
	std::vector<std::string> figFileFormats={"pdf"};
	int indexRow=-1;
	int indexColX=-1;
	int indexColY=-1;
	int indexColXunc=-1;
	int indexColYunc=-1;
	std::string plotType="";
	std::string notes="";

	std::vector<int> colours={kBlack, kRed, kGreen, kBlue, kYellow, kMagenta, kCyan, 12, kOrange-3, kSpring-6, kAzure-6, kViolet+1};
	std::vector<int> colours2={kAzure+3, kAzure+2, kAzure+1, kAzure+10, kAzure+6};
	std::vector<int> markers={20, 21, 22, 23, 20, 21, 22, 23, 33, 34, 29, 43, 24, 25, 26, 32, 27, 28, 30, 42};
	std::vector<double> markerSizes={1};
	float marginT=0.1;//seems like default 0.1
	float marginB=0.1;
	float marginL=0.1;
	float marginR=0.1;
	float xLabelSize=0.04;
	float yLabelSize=0.04;

	std::vector<int> TPadColours={1,861};//860 is kAzure
	TString drawOption="lp";

	//the min/max X and Y shown on this canvas
	double minX=-999;
	double maxX=-999;
	double minY=-999;
	double maxY=-999;
	double minXval;
	double maxXval;
	double minYval;
	double maxYval;
	std::vector<double> offsetsX={0.};//each element is for 1 file
	std::vector<double> offsetsY={0.};
	std::vector<double> factorsX={1.};
	std::vector<double> factorsY={1.};
	std::vector<std::vector<int>> fitPoints;

	void setValues(double theMinX, double theMaxX, double theMinY, double theMaxY, TString theTitle, TString theXaxis, TString theYaxis, TString theDrawOpt="", int theWidth=900, int theHeight=600){
		Xaxis=theXaxis; Yaxis=theYaxis; title=theTitle;
		minX=theMinX; maxX=theMaxX; minY=theMinY; maxY=theMaxY;
		drawOption=theDrawOpt;
		width=theWidth; height=theHeight;
	}

	void createTGEs(std::vector<std::vector<std::string>> configs){
		for (int i=0;i<configs.size();i++){
			TGE aTGE;
			TGEs.push_back(aTGE);
		}
	}

	// apply options to TGEs: offsets and factors, fileNames, indexColX, indexRow, indexColY, plotType, indexColXunc, indexColYunc
	void applyOptions(){
		// if offset same for every line in the plot, make a vector with the same value
		expandVector(offsetsX, fileNames.size(), 0, "X offset: ");
		expandVector(offsetsY, fileNames.size(), 0, "Y offset: ");
		expandVector(factorsX, fileNames.size(), 0, "X coefficient: ");
		expandVector(factorsY, fileNames.size(), 0, "Y coefficient: ");
		for (int i=0;i<fileNames.size();i++){
			TGEs[i].offsetX=offsetsX[i];
			TGEs[i].offsetY=offsetsY[i];
			TGEs[i].factorX=factorsX[i];
			TGEs[i].factorY=factorsY[i];
			TGEs[i].indexColX=indexColX;
			TGEs[i].indexColY=indexColY;
			TGEs[i].indexColXunc=indexColXunc;
			TGEs[i].indexColYunc=indexColYunc;
			TGEs[i].indexRow=indexRow;
			TGEs[i].setValues(cycVec(colours,i), markerSizes[0], cycVec(markers,i), legendEntries[i]);
			TGEs[i].drawOption=drawOption;//TODO is "same" unnecessary?
		}
	}

	void fill_data_allFiles(){
		data_allFiles={};
		for (int i=0;i<fileNames.size();i++){
			//std::cout<<"canOpts.fill_data_allFiles() idx "<<i<<"\n";
			data_allFiles.push_back(getData(fileNames[i]));
			//each element in the vector will store the data from one data file, and is likely one line on the plot
		}
		//std::cout<<"canOpts.fill_data_allFiles() done";
	}

	void fill_TGEs(std::vector<std::vector<std::vector<double>>> allXYvecs, int idx_start, int idx_end){
		for (int i=idx_start;i<idx_end;i++){
			TGraphErrors* aGraph=makeTGraphErrors(allXYvecs[i],TGEs[i]);
			TGEs[i].TGE_ptr=aGraph;
		}
		//canOpts.TGEs.push_back(aTGE);
	}

	void setVecInt(std::vector<std::vector<int>> allVecs, int idx_start, int idx_end){//TODO pass member as argument
		expandVector(allVecs, idx_end-idx_start);
		int j=0;
		std::cout<<"size of all fit ranges: "<<allVecs.size()<<"size of index range: "<<idx_end-idx_start<<"\n";
		for (int i=idx_start;i<idx_end;i++){
			TGEs[i].fitPoints=allVecs[j];
			j=j+1;
		}
	}

	void setTGEsValues(){
		for (int i=0;i<fileNames.size();i++){
		}
	}
};


// not used yet in other functions in this file
// e.g. plotOnCanvas(can, XYZvec, theNames, "p same");
void plotOnCanvas(TCanvas* can, std::vector<std::vector<double>> &theDataVec, std::vector<std::string> &theNames, std::string theOption=""){
	TGraphErrors* theTGraphErrors=new TGraphErrors;
	if (theDataVec.size()==2){
		int theNthPoint=0;
		for (int i=0;i<theDataVec[0].size();i++){
			theTGraphErrors->SetPoint(theNthPoint,theDataVec[0][i],theDataVec[1][i]);
			theNthPoint=theNthPoint+1;
		}
		theTGraphErrors->SetMarkerSize(1.25);
		theTGraphErrors->SetMarkerStyle(20);
		theTGraphErrors->Draw(theOption.c_str());
		
	}
}


TDatime convertTime(std::string theTime, std::string toPrint=""){
	// convert the string to numbers 2022-05-10_14:30
	int year=std::stoi(theTime.substr(0, 4));
	int month=std::stoi(theTime.substr(5, 7));
	int day=std::stoi(theTime.substr(8, 10));
	int hour=std::stoi(theTime.substr(11, 13));
	int minute=std::stoi(theTime.substr(14, 16));
	printString(toPrint,"the year, month, day, hour, minute: "+std::to_string(year)+" "+std::to_string(month)+" "+std::to_string(day)+" "+std::to_string(hour)+" "+std::to_string(minute)+"\n");
	TDatime da(year,month,day,hour,minute,00);
	return da;
}


// not used yet
// give a vector of relative t (normally as x axis) and the initial date&time, return the vector in absolute t
std::vector<double> relToAbsTime(TDatime startT, std::vector<double> tVec, std::string toPrint=""){
	std::vector<double> tVecAbs;
	int factor=60;
	for (int i=0;i<tVec.size();i++){
		tVecAbs.push_back(startT.Convert()+tVec[i]*factor);
	}
	return tVecAbs;
}


// this function is meant to provide a dummy graph to be able to setRangeUser as desired
//   between x1,y1 and x2,y2
TGraph* dummyGraph(double minX, double maxX, double minY, double maxY, TString title=""){
	TGraph* dummy = new TGraph(2);
	dummy->SetPoint(0,minX,minY);
	dummy->SetPoint(1,maxX,maxY);
	dummy->SetTitle(title);
	dummy->SetLineColor(0);
	dummy->SetMarkerColor(0);
	dummy->SetMarkerSize(0);
	dummy->GetXaxis()->SetRangeUser(minX,maxX);
	dummy->GetYaxis()->SetRangeUser(minY,maxY);
	return dummy;
}


// does not work yet and may not be needed
void limitRange(std::vector<std::vector<double>> XYvec,int whichEle, double vMin, double vMax){
	int start=0;
	int stop=XYvec[whichEle].size();
	// find out from which index to cut
	for(int i=0;i<XYvec[whichEle].size();i++){
		if (XYvec[whichEle][i]<vMin){
			start=i;
		}
		if (XYvec[whichEle][i]>vMin){
			stop=i;
		}
	}
}


std::vector<double> retAxisRange(TGraphErrors* theTGE){
	double xmin = theTGE->GetXaxis()->GetXmin();
	double xmax = theTGE->GetXaxis()->GetXmax();
	double ymin = theTGE->GetYaxis()->GetXmin();//GetYmin() does not exist
	double ymax = theTGE->GetYaxis()->GetXmax();//GetYmax() does not exist
	std::vector<double> theRange={xmin, xmax, ymin, ymax};
	return theRange;
}


void fillTGEaxisRange(TGE &theTGE){
	std::cout<<"in fillTGEaxisRange\n";
	std::vector<double> theRange=retAxisRange(theTGE.TGE_ptr);
	theTGE.minXval=theRange[0];
	theTGE.maxXval=theRange[1];
	theTGE.minYval=theRange[2];
	theTGE.maxYval=theRange[3];
	std::cout<<"The axis range for this TGraphErrors: "<<theTGE.minXval<<" "<<theTGE.maxXval<<" "<<theTGE.minYval<<" "<<theTGE.maxYval<<"\n";
}


TCanvas* initCan(canOptions &canOpts, TPad* &pad0, TPad* &pad1){
	TCanvas* can = new TCanvas(canOpts.title,canOpts.title+"_name", canOpts.width, canOpts.height);
	//std::cout<<"canOpts.title: "<<canOpts.title<<"\n";
	//can->SetTopMargin(0.01);//does nothing
	can->cd();
	gStyle->SetOptTitle(0);//?
	gStyle->SetPadTopMargin(canOpts.marginT);// default 0.1
	gStyle->SetPadBottomMargin(canOpts.marginB);// default 0.1
	gStyle->SetPadLeftMargin(canOpts.marginL);// default 0.1
	gStyle->SetPadRightMargin(canOpts.marginR);// default 0.1
	TGaxis::SetMaxDigits(3);

	pad0 = new TPad("pad0", "", 0., 0., 1, 1);//the TPad that fills the whole canvas
	//pad0->SetFillColor(kRed-7);//pad0->GetFillColor() gives 625
	pad0->Draw();

	//gPad is always pointing to the active pad
	//std::cout<<"colour: "<<gPad->GetFillColor()<<"\n";
	// no active pad before cd

	pad1 = new TPad("pad1", "", 0., 0., 0.75, 1);
	pad1->SetFillStyle(4000);//transparent
	pad1->Draw();
	pad1->SetGrid();
	//pad1->SetFillColor(kYellow-7);//393
	//double x1;double y1;double x2;double y2;
	//pad1->GetRange(x1, y1, x2, y2);
	//std::cout<<"Initial pad1->GetRange:\n"<<x1<<" "<<x2<<" "<<y1<<" "<<y2<<"\n";//0 1 0 1
	TGraph* dummy=dummyGraph(canOpts.minX,canOpts.maxX, canOpts.minY,canOpts.maxY, canOpts.title);
	//std::cout<<"canOpts extremes: "<<canOpts.minX<<" "<<canOpts.maxX<<" "<<canOpts.minY<<" "<<canOpts.maxY<<"\n";
	dummy->GetXaxis()->SetTitle(canOpts.Xaxis);
	dummy->GetXaxis()->SetTitleOffset(1.05);
	dummy->GetXaxis()->SetLabelSize(canOpts.xLabelSize);
	dummy->GetXaxis()->SetTitleSize(canOpts.xLabelSize);
	//std::cout<<"canOpts.xLabelSize: "<<canOpts.xLabelSize<<"\n";
	dummy->GetYaxis()->SetTitle(canOpts.Yaxis);
	//std::string Yaxis_str(canOpts.Yaxis);//convert TString to std::string
	dummy->GetYaxis()->SetTitleOffset(1.25);
	dummy->GetYaxis()->SetLabelSize(canOpts.yLabelSize);
	dummy->GetYaxis()->SetTitleSize(canOpts.yLabelSize);
	pad1->cd();
	dummy->Draw("ap");// this must be "ap" // pad1 range still 0 1 0 1
	//dummy->Draw(canOpts.drawOption);// pad1 range still 0 1 0 1
	//std::cout<<canOpts.drawOption<<endl;
	canOpts.TPads[0]=pad0;
	canOpts.TPads[1]=pad1;
	return can;
}


//parameters needed: allTGEs, can
//adds entry to legend
// how to draw two axes: https://root-forum.cern.ch/t/draw-two-graphs-on-one-canvas-with-different-y-scales/21755/6
// a good intro about TPad https://root.cern.ch/root/html534/guides/users-guide/Graphics.html
TCanvas* putGraphsOnCanvas(TCanvas* &can, TLegend* &canLeg, canOptions &canOpts, std::vector<TGE> allTGEs, TPad* &theTPad){
	if(DEBUG>2){std::cout<<"total # of graphs to be drawn: "<<allTGEs.size()<<"\n";}
	can->cd();
	theTPad->Draw();
	theTPad->cd();
	for (int i=0;i<allTGEs.size();i++){
		TString theDrawOption=allTGEs[i].drawOption;
		//allTGEs[i].TGE_ptr->Print();//for debugging, prints out the data
		allTGEs[i].TGE_ptr->Draw(theDrawOption);
		//std::cout<<theDrawOption<<endl;
		canLeg->AddEntry(allTGEs[i].TGE_ptr, allTGEs[i].legend, theDrawOption);
	}
	//gPad->Update();
	//can->Update();
	//gPad->Update();//pad1->Update();//does not work?
	//can->Show();
	return can;
}


TCanvas* putGraphsOnCanvas(TCanvas* &can, std::vector<TLine*> allTLines, TPad* &theTPad){
	std::cout<<"# of TLines to be drawn: "<<allTLines.size()<<"\n";
	can->cd();
	theTPad->Draw();
	theTPad->cd();
	for (int i=0; i<allTLines.size(); i++){
		allTLines[i]->Draw();
		//theTPad->Update();
		gPad->Update();
	}
	return can;
}


// finds the min and max of X and Y in alltheTGEs, and fill them into theCanOpts.minXval, maxXval, minYval, maxYval
void fillCanAxisRange(std::vector<TGraphErrors*> &allTheTGEs, canOptions &theCanOpts){//std::vector<TGE> &theTGE){
	//std::cout<<"# of graphs to be drawn on pad2 (allTheTGEs.size()): "<<allTheTGEs.size()<<"\n";
	std::vector <std::vector<double>> allRanges;
	std::vector<double> theRange;
	for (int i=0;i<allTheTGEs.size();i++){
		theRange=retAxisRange(allTheTGEs[i]);
		//printVector(theRange,"the range: ");
		allRanges.push_back(theRange);
	}
	std::vector<double> minXvals;
	std::vector<double> maxXvals;
	std::vector<double> minYvals;
	std::vector<double> maxYvals;
	//std::cout<<"how many ranges to be taken into consideration: "<<allRanges.size()<<"\n";
	for (int i=0;i<allRanges.size();i++){
		minXvals.push_back(allRanges[i][0]);
		maxXvals.push_back(allRanges[i][1]);
		minYvals.push_back(allRanges[i][2]);
		maxYvals.push_back(allRanges[i][3]);
	}
	//find the min of the mins and the max of the maxes
	theCanOpts.minXval=findMinMaxAvg(minXvals,"min");
	theCanOpts.maxXval=findMinMaxAvg(maxXvals,"max");
	theCanOpts.minYval=findMinMaxAvg(minYvals,"min");
	theCanOpts.maxYval=findMinMaxAvg(maxYvals,"max");
	std::cout<<"The axis range for all the TGraphErrors: "<<theCanOpts.minXval<<" "<<theCanOpts.maxXval<<" "<<theCanOpts.minYval<<" "<<theCanOpts.maxYval<<"\n";
}


// range of new TPad initialised according to the exiting TPad
void initNewTPad(TCanvas* &can, TLegend* &canLeg, canOptions &canOpts2, std::vector<TGraphErrors*> allGraphs2, std::vector<TGE> allTGEs2, TPad* &pad2, TPad* pad1){
	//can->cd();// without this, pad2 has size same as pad1 even if used 0., 0., 1.0, 1.0
	if(DEBUG>2){std::cout<<"# of graphs to be drawn on pad2: "<<allGraphs2.size()<<"\n";}
	//pad2 = new TPad("pad2", "", 0.0, 0.0, 1.0, 1.0);
	pad2 = new TPad("pad2", "", 0., 0., 0.75, 1.0);
	pad2->Draw();
	pad2->cd();
	/*// this moves everything (include legend) a bit left, somehow
	gStyle->SetPadTopMargin(canOpts2.marginT);
	gStyle->SetPadBottomMargin(canOpts2.marginB);
	gStyle->SetPadLeftMargin(canOpts2.marginL);
	gStyle->SetPadRightMargin(canOpts2.marginR);
	*/
	//pad2->SetFillColorAlpha(kAzure-9,0.5);//1179
	//std::cout<<"colour 2: "<<pad2->GetFillColor()<<"\n";
	pad2->SetFillStyle(4000);//transparent

	fillCanAxisRange(allGraphs2,canOpts2);
	//std::cout<<"canOpts2.maxY: "<<canOpts2.maxY<<" canOpts2.maxYval: "<<canOpts2.maxYval<<"\n";//maxY is still that of canOpts
	// plot the whole range of Y+extra, but for X, follow the values for pad1
	int extraY=(canOpts2.maxYval-canOpts2.minYval);
	canOpts2.minY=canOpts2.minYval;
	canOpts2.maxY=canOpts2.maxYval+extraY;
	float padXlength=(canOpts2.maxX-canOpts2.minX)/(1-(canOpts2.marginL+canOpts2.marginR));
	float padXminV=canOpts2.minX-padXlength*canOpts2.marginL;
	float padXmaxV=canOpts2.maxX+padXlength*canOpts2.marginR;
	float padYlength=(canOpts2.maxY-canOpts2.minY)/(1-(canOpts2.marginT+canOpts2.marginB));
	float padYminV=canOpts2.minY-padYlength*canOpts2.marginB;
	float padYmaxV=canOpts2.maxY+padYlength*canOpts2.marginT;
	//double xmin = pad1->GetUxmin();
	//double xmax = pad1->GetUxmax();
	//double dx = xmax-xmin;
	//double dy = (canOpts2.maxYval+extraY - canOpts2.minYval);
	//float padXmin=xmin-marginL*dx;// is this really the min and max of the pad?
	//float padXmax=xmax+marginR*dx;
	//float padYmin=canOpts2.minYval-marginB*dy;
	//float padYmax=canOpts2.maxYval+extraY+marginT*dy;
	//std::cout<<"xmin: "<<xmin<<"padXmin: "<<padXmin<<"\n";
	//pad2->Range(padXmin,padYmin,padXmax,padYmax);
	//canOpts2.minX=xmin;
	//canOpts2.maxX=xmax;
	//canOpts2.minY=canOpts2.minYval;
	//canOpts2.maxY=canOpts2.maxYval+extraY;
	//pad2->Range(canOpts2.minXval,canOpts2.minYval,canOpts2.maxXval,canOpts2.maxYval);//cover whole pad
	pad2->Range(padXminV,padYminV,padXmaxV,padYmaxV);
	//somehow putting 2nd yaxis here doesn't work
}


void drawLegend(TCanvas* &can, TLegend* &canLeg, TPad* &theTPad){
	can->cd();
	canLeg->SetBorderSize(0);//gets rid of the black boarder around the legend
	canLeg->SetFillColor(0);
	//canLeg->SetHeader("The Legend Title","C");
	theTPad->cd();
	canLeg->Draw();
	can->Update();
}


void addYaxis(TCanvas* &can, canOptions &canOpts2, TPad* &theTPad){
	can->cd();
	theTPad->cd();
	//TGaxis* yaxis2 = new TGaxis(da1.Convert()+dx, canOpts2.minYval, da1.Convert()+dx, canOpts2.maxYval+extraY, canOpts2.minYval, canOpts2.+extraY, 510, "+L");
	TGaxis* yaxis2 = new TGaxis(canOpts2.maxX, canOpts2.minY, canOpts2.maxX, canOpts2.maxY, canOpts2.minY, canOpts2.maxY, 510, "+L");
	yaxis2->SetLineColor(860+1);
	yaxis2->SetLabelColor(860+1);
	yaxis2->SetTitle("RH [%]");
	yaxis2->SetTitleOffset(1.0);
	yaxis2->SetTitleColor(860+1);
	yaxis2->Draw();
}


void addTimeAxis(TCanvas* &can, canOptions &canOpts2, TDatime da1, TPad* &theTPad, int idx, float moveDown){
	can->cd();
	theTPad->cd();
	theTPad->Draw();

	unsigned int dx = (canOpts2.maxX-canOpts2.minX)*60*60;
	float yRange=canOpts2.maxY-canOpts2.minY;
	float add1st=0.45;
	moveDown=moveDown*((idx+1)+add1st)*yRange;
	TGaxis* timeAxis=new TGaxis(canOpts2.minX, canOpts2.minY-moveDown, canOpts2.maxX, canOpts2.minY-moveDown, 0, dx, 612, "+LtS");
	//TGaxis* timeAxis=new TGaxis(canOpts2.minX, canOpts2.maxY, canOpts2.maxX, canOpts2.maxY, 0, dx, 510, "-LtS");
	timeAxis->SetTimeOffset(da1.Convert());
	timeAxis->SetTimeFormat("%H:%M");
	//timeAxis->SetTimeFormat("#splitline{%Y-%m-%d}{%H:%M}");
	//timeAxis->SetTimeFormat("%d-%m-%Y");
	timeAxis->SetLabelSize(canOpts2.xLabelSize);
	timeAxis->SetLineColor(canOpts2.colours2[idx]);
	timeAxis->SetLabelColor(canOpts2.colours2[idx]);

	theTPad->cd();
	timeAxis->Draw();
	theTPad->Draw();
}


// save the figure
void saveCan(TCanvas* can, canOptions canOpts){
	// a list of available formats can save in. If what was specified is available, save in this format. If not, say it
	//printVector(canOpts.figFileName,"The figure(s) will be saved under this name: ");
	//printVector(canOpts.figFileFormats,"The figure(s) will be saved in these formats: ");
	std::vector<std::string> availableFormats={"png","pdf"};
	if (canOpts.figFileName!=""){
		for (int i=0;i<(canOpts.figFileFormats).size();i++){
			int theFoundIndex=findItemInVector(availableFormats,canOpts.figFileFormats[i]);
			//std::cout<<"!!! "<<i<<" the found index: "<<theFoundIndex<<"\n";
			if ((theFoundIndex)!=-1){
				TString outputFileName=canOpts.outputFolder+canOpts.figFileName+"."+canOpts.figFileFormats[i];
				can->Print(outputFileName);
			}else{
				printVector(canOpts.figFileFormats,"you wanted to save the figure(s) in these formats: ");
				std::cout<<"specified format \""<<canOpts.figFileFormats[i]<<"\" not available! Please use all lower case letters, if haven't done so already\n";
			}
		}
	}
}


//write a function that takes an input TGraphErrors and outputs a .txt file with all the values that have been plotted
void plottedGraphValues(TGraphErrors* graph, std::string Xtitle, std::string Xtitle_new, std::string Ytitle, std::string Ytitle_new, std::string YEtitle, std::string YEtitle_new, std::string outputFileName, std::vector<std::vector<std::string>> theDataPoints){
	std::vector<std::vector<std::string>> theDataPoints2;
	int N; int V_column; int I_column; int err_column=-1; int title_row=-1; int title_row_check=-1;
	theDataPoints2=theDataPoints;
	N=graph->GetN();

	printVectorVector(theDataPoints);

	//find the x-values as an array, convert to vector of strings
	double* X = graph->GetX();
	std::vector<std::string> Xvalues;		
	for (int i=0; i<N; i++){
		Xvalues.push_back(to_string(X[i]));	//voltage
	}
	//find the y-values as an array, convert to vector of strings
	double* Y = graph->GetY();
	std::vector<std::string> Yvalues;
	for (int i=0; i<N; i++){
		Yvalues.push_back(to_string(Y[i]));	//current
	}
	//find the error in x-values as an array, convert to vector of strings (note this part is probably not going to be used)
	double* EX = graph->GetEX();
	std::vector<std::string> EXvalues;
	for (int i=0; i<N; i++){
		EXvalues.push_back(to_string(EX[i]));	//error in voltage (usually not measured, assumed 0)
	}
	//find the error in y-values as an array, convert to vector of strings
	double* EY = graph->GetEY();
	std::vector<std::string> EYvalues;
	for (int i=0; i<N; i++){
		EYvalues.push_back(to_string(EY[i]));	//error in current
	}	

	//now add to one big vector of vectors of doubles
	std::vector<std::vector<std::string>> XYvalues;
	XYvalues.push_back(Xvalues);	//V
	XYvalues.push_back(Yvalues);	//I
	XYvalues.push_back(EXvalues);	//deltaV (0)
	XYvalues.push_back(EYvalues);	//deltaI
	//find the title row number and column numbers of data to correct
	for(int j=0; j<theDataPoints.size(); j++){
		for (int i=0; i<theDataPoints[j].size(); i++){
			if (theDataPoints[j][i].find(Xtitle)!=std::string::npos){
				V_column=i;
				title_row=j;
				std::cout<<"the row number for "<<Xtitle<<" is: "<<title_row<<std::endl;
				std::cout<<"the column number for "<<Xtitle<<" is: "<<V_column<<std::endl;
			}else if (theDataPoints[j][i].find(Ytitle)!=std::string::npos){
				I_column=i;
				title_row_check=j;
				std::cout<<"the row number for "<<Ytitle<<" is: "<<title_row_check<<std::endl;
				std::cout<<"the column number for "<<Ytitle<<" is: "<<I_column<<std::endl;
			}else if (theDataPoints[j][i].find(YEtitle)!=std::string::npos){
				err_column=i;
				std::cout<<"the row number for "<<YEtitle<<" is: "<<j<<std::endl;
				std::cout<<"the column number for "<<YEtitle<<" is: "<<err_column<<std::endl;
			}
		}
	}
	//TODO there seem to be a bug somewhere, if delete printout, got error
	std::cout<<"1\n";
	//check:
	if (title_row!=title_row_check){
		std::cout<<"***CHECK TITLE ROW***"<<std::endl;
	}
	std::cout<<"2\n";
	//now replace original data with graphed data
	for (int j=title_row; j<theDataPoints.size(); j++){
		if (j==title_row){
			theDataPoints2[j][V_column] = Xtitle_new;
			theDataPoints2[j][I_column] = Ytitle_new;
			if(err_column>=0){theDataPoints2[j][err_column] = YEtitle_new;}
		}else if (j>title_row){	
			theDataPoints2[j][V_column] = XYvalues[0][j-title_row-1];
			theDataPoints2[j][I_column] = XYvalues[1][j-title_row-1];
			if(err_column>=0){theDataPoints2[j][err_column] = XYvalues[3][j-title_row-1];}
		}
	}
	std::cout<<"3\n";
	//save in new .txt file
	saveTxt(theDataPoints2, outputFileName);
	std::cout<<"4\n";
}


//take canOptions, where there're data_allFiles
//TGEs which contain indexColX(Y), indexRow, offsetX(Y), factorX(Y), indexColXunc
//return a list of 4-element-vectors
std::vector<std::vector<std::vector<double>>> getXYvecs(canOptions canOpts, int idx_start, int idx_end){
	std::vector<std::vector<std::vector<double>>> allXYvecs;
	//std::cout<<"in getXYvecs!"<<"idx_start: "<<idx_start<<" idx_end: "<<idx_end<<"\n";
	for (int i=idx_start;i<idx_end;i++){//loop through all files
		// XYvec stores the X vals, Y vals, X unc, Y unc
		std::vector<std::vector<double>> XYvec;
		//printVectorVector(canOpts.data_allFiles[i],"everything: ");
		std::vector<double> Xvec=getData_vector(canOpts.data_allFiles[i],canOpts.TGEs[i].indexColX,canOpts.TGEs[i].indexRow,canOpts.TGEs[i].offsetX,canOpts.TGEs[i].factorX);
		XYvec.push_back(Xvec);
		std::vector<double> Yvec=getData_vector(canOpts.data_allFiles[i],canOpts.TGEs[i].indexColY,canOpts.TGEs[i].indexRow,canOpts.TGEs[i].offsetY,canOpts.TGEs[i].factorY);
		//std::cout<<"idxColY="<<canOpts.TGEs[i].indexColY<<" idxRow="<<canOpts.TGEs[i].indexRow<<" oY="<<canOpts.TGEs[i].offsetY<<" fY="<<canOpts.TGEs[i].factorY<<"\n";
		XYvec.push_back(Yvec);

		// add uncertainties into XYvec
		if(DEBUG>2){printVector(Yvec, "the data (Yvec) extracted from file: ");}
		std::vector<double> XvecUnc={};
		std::vector<double> YvecUnc={};
		if (canOpts.TGEs[i].indexColXunc>0){
			XvecUnc=getData_vector(canOpts.data_allFiles[i],canOpts.TGEs[i].indexColXunc,canOpts.TGEs[i].indexRow,0.0,TMath::Abs(canOpts.TGEs[i].factorX));//offset does not play any role in uncertainty, factor use absolute value
		}else{
			XvecUnc={0.0}; expandVector(XvecUnc, XYvec[0].size());
		}
		XYvec.push_back(XvecUnc);
		if(DEBUG>2){printVector(XYvec[2],"! X unc: ");}
		if (canOpts.indexColYunc>0){
			YvecUnc=getData_vector(canOpts.data_allFiles[i],canOpts.TGEs[i].indexColYunc,canOpts.TGEs[i].indexRow,0.0,TMath::Abs(canOpts.TGEs[i].factorY));
		}else{
			YvecUnc={0.0}; expandVector(YvecUnc, XYvec[1].size());
		}
		XYvec.push_back(YvecUnc);

		//print, add to total list
		if(DEBUG>2){printVector(XYvec[3],"! Y unc: ");}
		//TODO write a function to limit the values only to a certain range
		//limitRange(XYvec);
		std::cout<<canOpts.fileNames[i]<<"\n";
		printVector(Xvec,"X: ");
		printVector(Yvec,"Y: ");
		allXYvecs.push_back(XYvec);
	}
	return allXYvecs;
}




//===============================
//------ ------ fit ------ ------
//===============================

// fit a TGraphErrors* at certain x range
//TODO what if x2 < x1
//g->Fit("slope", "QW", "", x2, x1);
// x1 x2 used -3,3 or 0.8,-1 before
std::vector<double> fit_line(TGraphErrors* g, double x1, double x2){
	//fitting functions
	TF1* slope=new TF1("slope", "[0]*x+[1]", 0, 250);
	slope->SetParameters(1,1);//set any (maybe) initial parameters
	//prefit, result will be used in final fit
	//probably because used name "slope"
	//Q: Quiet mode (minimum printing)
	//W: Set all weights to 1 for non empty bins; ignore error bars (WW incl empty bins)
	//M: Improve fit results, by using the IMPROVE algorithm of TMinuit.
	//0: Do not plot the result of the fit
	g->Fit("slope", "QW0", "", x1, x2);//not sure if 0 made difference
	double k = slope->GetParameter(0);
	double b = slope->GetParameter(1);
	//std::cout<<"prefit gradient = "<<k<<" intercept = "<<b<<std::endl;
	//final fit
	g->Fit("slope", "QM0", "", x1, x2);
	k = slope->GetParameter(0);
	b = slope->GetParameter(1);
	//std::cout<<"final fit gradient = "<<k<<" intercept = "<<b<<std::endl;
	double k_unc = slope->GetParError(0);
	double b_unc = slope->GetParError(1);

	std::vector<double> fit_result = {k,b,k_unc,b_unc};
	return fit_result;
}


// do not want to change g
// params: p_range={start point, end point}, count from 0
// TODO if factorsX=-1, data is ordered positive to negative
// So GetPointX(lower number) gives larger X...
// Means x2 < x1
// p1 and p2 are indices between which are included in the fit
// p1 count from 0, p2 count from the back, both inclusive
std::vector<double> fit_line(TGraphErrors* g, int p1, int p2){
	double x1 = g->GetPointX(p1);
	std::cout<<"p1="<<p1<<" x1="<<x1<<std::endl;
	double x2 = g->GetPointX(g->GetN()-p2-1);
	std::cout<<"total nof points N="<<g->GetN()<<std::endl;//like .size()
	std::cout<<"p2="<<p2<<" x2="<<x2<<std::endl;

	std::vector<double> fit_result=fit_line(g, x1, x2);

	double k=fit_result[0];
	double b=fit_result[1];
	double k_unc=fit_result[2];
	double b_unc=fit_result[3];
	//std::cout<<"fit results (k, b, k unc, b unc): "<<k<<" "<<b<<" "<<k_unc<<" "<<b_unc<<"\n";
	//fit results (slope, intercept, resistance): 4.09317 -0.0721985 244.31
	double y1=k*x1+b;
	double y2=k*x2+b;
	std::cout<<"y1="<<y1<<" y2="<<y2<<std::endl;
	fit_result.push_back(x1);
	fit_result.push_back(y1);
	fit_result.push_back(x2);
	fit_result.push_back(y2);

	return fit_result;
}


//==================================
//------ ------ sensor ------ ------
//==================================

//Define function to normalise current readings to 20 deg C (chiller temperature... not sure if this is relevant)
double normaliseI(double I, double T /* units of K*/, double E_g /* units of eV*/, double targetT=20){
	const double k = 1.380649*pow(10,(-23)); //m^2 kg s^-2 K^-1
	const double e = 1.602177*pow(10,(-19)); //coulombs
	return pow(T/(273.15+targetT), 2) * exp(E_g * e * (273.15+targetT-T)/(2*k*T*(273.15+targetT))) * I;// note units of E_g are in eV, and note the conversion of 20 deg C to 293.15 K
}


/*
		//correct for temperature fluctuations
		if (canOpts.plotType.find("correctT")!=std::string::npos){
			std::vector<double> Tvec=getData_vector(canOpts.data_allFiles[i],4,canOpts.indexRow,273.15,1.);
			for (int j=0; j<Yvec.size(); j++){
				Yvec[j] = normaliseI(Yvec[j], Tvec[j], 1.12,-25);
			}
		}
*/


//try and generalise to apply corrections to IV
void correctionsToData(std::vector<std::vector<std::string>> theDataPoints, int p, canOptions &canOpts, std::string outputFileName, int startRow, std::string subtitle){
    //startRow=6 for CV, 5 for IV and It
    //need to define second vector of vectors of strings containing the current corrected for temperature   
    std::vector<std::vector<std::string>> newDataPoints;
    //extract temperature values in K (conversion: add 273.15)  
    //if statement accounts for repeats inserting an extra row
    std::vector<double> Zvec;

    if (theDataPoints[7].size()==6){
       Zvec=getData_vector(theDataPoints,3,startRow,273.15,1.);//temperature
        //printVector(theDataPoints[7]);
        //std::cout<<"temp is "<<Zvec[1]<<std::endl;
    }else if (theDataPoints[7].size()==7){
        Zvec=getData_vector(theDataPoints,4,startRow,273.15,1.);//temperature
        //printVector(theDataPoints[7]);
        //std::cout<<"temp is "<<Zvec[1]<<std::endl;
   }
   //printVector(Zvec);

    std::vector<double> Xvec=getData_vector(theDataPoints,1,startRow,canOpts.offsetsX[p],canOpts.factorsX[p]);
    std::vector<double> Yvec=getData_vector(theDataPoints,2,startRow,canOpts.offsetsY[p],canOpts.factorsY[p]);
    std::vector<double> Yvec_Tcorr;
    //now map normaliseI over Xvec and Zvec, using bandgap of silicon as 1.12eV
    for (int q=0; q < Xvec.size(); q++){
        Yvec_Tcorr.push_back(normaliseI(Yvec[q], Zvec[q], 1.12));
    }

    //loop through theDataPoints
    for (int j=0; j<theDataPoints.size(); j++){
        if (j<startRow){
            newDataPoints.push_back(theDataPoints[j]);
            }else if (j==startRow){
                theDataPoints[j].push_back(subtitle);
                newDataPoints.push_back(theDataPoints[j]);
            }else{
                if(startRow==5){
                    theDataPoints[j].push_back(std::to_string(Yvec_Tcorr[j-6]));
                }else if(startRow==6){
                    theDataPoints[j].push_back(std::to_string(Yvec[j-7]));
                }
                newDataPoints.push_back(theDataPoints[j]);
            }
    }
    saveTxt(newDataPoints, outputFileName);
}


//produces text file with readings corrected for temperature
void correctByT(canOptions &canOpts, std::vector<TGraphErrors*> &allGs, std::vector<TGE> &allTGEs, std::vector<std::vector<std::string>> theDataPoints, std::vector<std::vector<double>> XYvec, int theIndex=0){
		std::vector<std::vector<double>> XYvec2;
		//extract temperature values in K (conversion: add 273.15)
		std::vector<double> Zvec=getData_vector(theDataPoints,3,5,273.15,1.);//temperature
		std::vector<double> Yvec_Tcorr;//current corrected for temperature on y-axis

		//now map normaliseI over Xvec and Zvec, using bandgap of silicon as 1.12eV
		std::vector<double> Xvec=XYvec[0];
		std::vector<double> Yvec=XYvec[1];
		for (int j=0; j < Xvec.size(); j++){
			Yvec_Tcorr.push_back(normaliseI(Yvec[j], Zvec[j], 1.12));
		}	

		//function to normalise current values is:
		//double normaliseI(double I, double T, double E_g)
		XYvec2.push_back(Xvec);//for T correction
		XYvec2.push_back(Yvec_Tcorr);

		//double fluc2=calcFluctuation(Yvec_Tcorr, "fluctuation if corrected by temperature: ");

		//print temperature values in K (seems to work)
		//printVector(Zvec);
		//corrections for T
		TGE aTGE2; aTGE2.setValues(cycVec(canOpts.colours,theIndex), canOpts.markerSizes[0], cycVec(canOpts.markers,theIndex), canOpts.legendEntries[theIndex]+" correction for T");//TODO fix line colour
		TGraphErrors* aGraph2=makeTGraphErrors(XYvec2,aTGE2);
		allGs.push_back(aGraph2);// this is a vector that contains all TGraphErrors
		aTGE2.drawOption=canOpts.drawOption;
		aTGE2.whichTPad=1;
		allTGEs.push_back(aTGE2);

		// produce text file with corrected readings in
		correctionsToData(theDataPoints, theIndex, canOpts, "data_T_corr"+canOpts.legendEntries[theIndex], 5, "I_corr/nA");
}


double calcFluctuation(std::vector<double> Yvec, std::string toPrint=""){
	//print out the fluctuation
	if(toPrint!=""){
		std::cout<<toPrint;
	}
	double theMin=findMinMaxAvg(Yvec,"min");
	double theMax=findMinMaxAvg(Yvec,"max");
	double theAvg=findMinMaxAvg(Yvec,"avg");
	double thePerc=(theMax-theMin)/theAvg*100;
	std::cout<<"minimum: "<<theMin<<" maximum: "<<theMax<<" average: "<<theAvg/*<<" temperature in K is :"<<Xvec*/<<" (max-min)/avg[%]: "<<thePerc<<"\n";
	return thePerc;
}



//Define a function to find the depletion voltage from a 1/C^2-V curve
std::vector<double> findVdep(TGraphErrors* g, double l1_x1, double l1_x2, double l2_x1, double l2_x2, double curve_dx){
	//fitting functions
	TF1* slope=new TF1("slope", "[0]*x+[1]", 0, 250);
	slope->SetParameters(1,1);
	TF1* constant=new TF1("constant", "[0]", 0, 250);
	constant->SetParameter(0,1);
	//prefit
	g->Fit("slope", "QW", "", l1_x1, l1_x2);
	g->Fit("constant", "Q+", "", l2_x1, l2_x2);

	//first approximation of Vdep is from intersection of prefit functions
	//slope has y=mx+b
	//constant has y=c
	//intersection when c=mx+b -> x=(c-b)/m
	double m = slope->GetParameter(0);
	double b = slope->GetParameter(1);
	double c = constant->GetParameter(0);
	double Vdep[2] = {};
	Vdep[0] = (c-b)/m;

	
	//final fit
	//option M improves fit with TMinuit algorithm
	g->Fit("slope", "QM0", "", l1_x1, Vdep[0]-curve_dx/2);	//0 option stops fit being printed on g, W option ignores point errors
	g->Fit("constant", "QM0+", "", Vdep[0]+curve_dx/2, l2_x2);	//0 option stops fit being printed on g, W option ignores point errors


	//calculate and print Vdep from final fit
	m = slope->GetParameter(0);
	b = slope->GetParameter(1);
	c = constant->GetParameter(0);
	Vdep[0] = (c-b)/m;
	
	//calculate error
	double mErr = slope->GetParError(0);
	double bErr = slope->GetParError(1);
	double cErr = constant->GetParError(0);
	//check expression below?
	Vdep[1] = sqrt(pow(mErr*(c-b)/(m*m),2) + pow(bErr/m, 2) + pow(cErr/m, 2));
	std::cout<<"depletion voltage: "<<Vdep[0]<<"V +- "<<Vdep[1]<<"V\n";
	//std::cout<<"the error in the depletion voltage is: "<<Vdep[1]<<" V"<<endl;

	std::vector<double> mbcVdepParameters = {m,b,c,Vdep[0],Vdep[1]};
	return mbcVdepParameters;
} 


//determine Vdep from the data points
std::vector<double> findVdepFromPoints(TGraphErrors *g, int l1_p1, int l2_p2, int l1_n, int l2_n, int curve_n){
	//l1_p1 = no. of points cut from beginning of g	
	//l2_p2 = no. of points cut from end of g
	//l1_n = no. of points used from beginning of cut g
	//l2_n = no. of points used from end of cut g
	//curve_n = no. of points in curved area, cut from final fit
	double l1_x1 = g->GetPointX(l1_p1+1);
	double l1_x2 = g->GetPointX(l1_p1+l1_n+1);
	double l2_x1 = g->GetPointX(g->GetN()-l2_p2-l2_n);
	double l2_x2 = g->GetPointX(g->GetN()-l2_p2-1);
	double curve_dx = (g->GetPointX(l1_p1+1)-g->GetPointX(l1_p1))*curve_n;
	std::vector<double> theFitRange={l1_x1, l1_x2, l2_x1, l2_x2, curve_dx};
	return theFitRange;
}


// did not pass theGraphToFit by referencing because don't want to interfere with it
// but does change theTGEs and allTLines
//fitRes=addCVfit(aGraph2, aTGE2, allTLines, fitPoints);//must be here since the function changes aTGE2, use if want to fit constant
std::vector<double> addCVfit(TGraphErrors* theGraphToFit, TGE &theTGEs, std::vector<TLine*> &allTLines, std::vector<int> fitPoints={2,2,6,6,2}){
	// set default values of fitting range and curvewidth
	int l1_p1 = fitPoints[0];
	int l2_p2 = fitPoints[1];
	int l1_n = fitPoints[2];
	int l2_n = fitPoints[3];
	int curve_n = fitPoints[4];
	std::vector<double> fitRange=findVdepFromPoints(theGraphToFit, l1_p1, l2_p2, l1_n, l2_n, curve_n);
	double l1_x1=fitRange[0]; double l1_x2=fitRange[1]; double l2_x1=fitRange[2]; double l2_x2=fitRange[3]; double curve_dx=fitRange[4];

	std::vector<double> fittedLineParams=findVdep(theGraphToFit, l1_x1, l1_x2, l2_x1, l2_x2, curve_dx);
	double m=fittedLineParams[0];
	double b=fittedLineParams[1];
	double c=fittedLineParams[2];
	double Vdep=fittedLineParams[3];
	//double Vdep_unc=fittedLineParams[4];

	// round Vdep and add to legend
	std::string VdepStr=roundToStr(Vdep,1);
	theTGEs.legend=theTGEs.legend+" "+TString(VdepStr);
	std::cout<<"fit results (slope, intercept for line1, constant for plateau): "<<m<<" "<<b<<" "<<c<<" "<<Vdep<<", legend: "<<theTGEs.legend<<"\n";

	double x1=l1_x1;
	double y1=theGraphToFit->GetPointY(l1_p1+1);
	double x2=Vdep;
	double y2=m*x2+b;
	TLine* theRamp =new TLine(x1, y1, x2, y2);
	theRamp->SetLineColor(theTGEs.colour);
	allTLines.push_back(theRamp);
	TLine* theConst=new TLine(Vdep, c, l2_x2, c);
	theConst->SetLineColor(theTGEs.colour);
	allTLines.push_back(theConst);
	//std::cout<<"x1, y1, x2, y2: "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<"\n";
	return fittedLineParams;
}


// this can be used alone, but is currently used under oneOvC2_unc
std::vector<double> convertTo1overY2(std::vector<double> Y){
	std::vector<double> oneOverY2;
	for(int i=0; i<Y.size(); i++){
		oneOverY2.push_back(1./(Y[i]*Y[i]));
	}
	return oneOverY2;
}


// uses convertTo1overY2
std::vector<std::vector<double>> oneOvC2_unc(std::vector<double> C, std::vector<double> C_unc){
	std::vector<double> oneOverC2=convertTo1overY2(C);
	std::vector<std::vector<double>> res; res.push_back(oneOverC2);
	if (C_unc.size()==C.size()){
		std::vector<double> oneOverC2_unc;
		for(int i=0; i<C.size(); i++){
			if(C[i]!=0){
				oneOverC2_unc.push_back(2*(C_unc[i]/C[i])*oneOverC2[i]);
			}else{
				std::cout<<"detected 0!!!!!! cannot use as denominator, appending -9999";
				oneOverC2_unc.push_back(-9999);
			}
		}
		res.push_back(oneOverC2_unc);
	}else{
		std::cout<<"trying to calculate uncertainty of 1/C^2, somehow C and C_unc have different size! This should not happen!";
		printVector(C,"C: ");
		printVector(C_unc,"C_unc: ");
	}
	return res;
}


// make a 3D vector that contains all 1/C^2 data
// from a 3D vector of {V, C, Vunc, Cunc}s
// uses oneOvC2_unc
std::vector<std::vector<std::vector<double>>> getXYvecs_1overC2(std::vector<std::vector<std::vector<double>>> allXYvecs){
	std::vector<std::vector<std::vector<double>>> allXYvecs_ret;
	for(int i=0;i<allXYvecs.size();i++){
		std::vector<std::vector<double>> XYvec=allXYvecs[i];
		std::vector<std::vector<double>> XYvec2;
		std::vector<std::vector<double>> YvecAndUnc=oneOvC2_unc(XYvec[1],XYvec[3]);
		XYvec2.push_back(XYvec[0]);
		XYvec2.push_back(YvecAndUnc[0]);
		//printVector(YvecAndUnc[0],"1/C^2: ");
		std::vector<double> Xunc2={0.0};
		std::vector<double> Yunc2={0.0};
		if (XYvec.size()==4){
			Xunc2=XYvec[2];
			Yunc2=YvecAndUnc[1];
		}else{
			expandVector(Xunc2, XYvec[0].size());
			expandVector(Yunc2, XYvec[1].size());
		}
		XYvec2.push_back(Xunc2); XYvec2.push_back(Yunc2);
		if(DEBUG>3){printVector(Yunc2,"uncertainty of 1/C^2: "); std::cout<<"XYvec2.size(): "<<XYvec2.size()<<"\n";}
		std::cout<<"converting vector "<<i<<" into 1overC2\n";
		printVector(XYvec2[0],"X: ");
		printVector(XYvec2[1],"Y: ");
		allXYvecs_ret.push_back(XYvec2);
	}
	return allXYvecs_ret;
}


		/*
		// if It, calculate fluctuation, add RH
		if(canOpts.plotType.find("It")!=std::string::npos){
			// calculate fluctuation and add it to the legend
			double fluc=calcFluctuation(Yvec);
			std::string flucStr=roundToStr(fluc,1);
			canOpts.TGEs[i].legend=canOpts.TGEs[i].legend+" "+TString(flucStr)+"%";
			//std::cout<<"i: "<<i<<", canOpts.TGEs[i].legend: "<<canOpts.TGEs[i].legend<<"\n";

			// add relative humidity to all gs
			TGE gOpts_RH; gOpts_RH.setValues(cycVec(canOpts.colours2,i), canOpts.markerSizes[1], cycVec(canOpts.markers,i), canOpts.legendEntries[i]+" RH"); gOpts_RH.drawOption=canOpts.drawOption;
			gOpts_RH.notes=canOpts.data_allFiles[i][2][2];// the date and time of the meas
			std::cout<<"this measurement was taken at: "<<gOpts_RH.notes<<"\n";
			std::vector<std::vector<double>> XYvec2;
			//std::vector<double> tVecAbs=relToAbsTime()
			XYvec2.push_back(Xvec);
			std::vector<double> Yvec2=getData_vector(canOpts.data_allFiles[i],5,canOpts.indexRow,0.,1.);//relative humidity on second y-axis
			XYvec2.push_back(Yvec2);

			TGraphErrors* aGraph_RH=makeTGraphErrors(XYvec2,gOpts_RH);
			allGs2.push_back(aGraph_RH);
			allTGEs2.push_back(gOpts_RH);
		}
	}
	

	// if the plot is It, plot RH on a second pad and add time axis
	// if don't want RH and extra time axis, simply comment out the following if
	if(canOpts.plotType.find("It")!=std::string::npos){//add the RH TGEs only later to not mess up the order
		TPad* pad2; canOptions canOpts2=canOpts; canOpts2.Xaxis=""; canOpts2.Yaxis="RH [%]"; canOpts2.colours=canOpts.colours2;canOpts2.colours2=canOpts.colours;
		initNewTPad(can, canOpts.legend, canOpts2, allGs2, allTGEs2, pad2, canOpts.TPads[1]);
		putGraphsOnCanvas(can, canOpts.legend, canOpts2, allGs2, allTGEs2, pad2);
		addYaxis(can, canOpts2, pad2);

		for (int i=0;i<allTGEs2.size();i++){
			std::string initialDateTime=allTGEs2[i].notes;
			if(DEBUG>3){cout<<"initialDateTime: "<<initialDateTime<<endl;}//2022-05-10_14:30
			TDatime da1=convertTime(initialDateTime);//2022 3 4 14 6
			addTimeAxis(can, canOpts2, da1, pad2, i, 0.06);//last parameter is frac of total y
		}
	*/


//uses fit_line (x values)
//fit, add R to legend, add TLines to TGE
//p1: start point (count from 1 from beginning)
//p2: end point (count from the back)
std::vector<TLine*> addFit_R_TLine(std::vector<TGE> &allGopts){
	int p1; int p2;
	std::vector<TLine*> allTLines;
	for (int i=0;i<allGopts.size();i++){
		p1=allGopts[i].fitPoints[0];
		printVector(allGopts[i].fitPoints,"fitPoints: ");
		p2=allGopts[i].fitPoints[1];
		std::cout<<"p1 p2="<<p1<<" "<<p2<<"\n";
		std::vector<double> fit_result=fit_line(allGopts[i].TGE_ptr, p1, p2);

		//calculate R
		//V = IR so R is inverse gradient of IV curve
		//error found directly from fit (combined)
		double k=fit_result[0];
		double b=fit_result[1];
		double k_unc=fit_result[2];
		double b_unc=fit_result[3];
		std::cout<<"fit result (k, b, k unc, b unc): "<<k<<" "<<b<<" "<<k_unc<<" "<<b_unc<<"\n";
		double R=1/k;
		//R[0] = 1000/m;
		double R_unc = k_unc/pow(k,2);
		//R[1] = 1000*mErr/pow(m,2);
		std::cout<<"inter-pixel resistance: "<<R<<" +- "<<R_unc<<" MOhms"<<endl;//" kOhms"<<endl;
		//inter-pixel resistance: 244.31 +- 0.00408363 kOhms

		// change legend
		TString R_TString=roundToStr(R, 2);
		allGopts[i].legend=allGopts[i].legend+" "+R_TString+" MOhm";//kOhm";

		// make the TLine
		double x1=fit_result[4];
		double y1=fit_result[5];
		double x2=fit_result[6];
		double y2=fit_result[7];
		//std::cout<<"y1="<<y1<<" y2="<<y2<<std::endl;
		TLine* aTLine=new TLine(x1, y1, x2, y2);//x2, y2, x1, y1 does not make a difference
		aTLine->SetLineColor(1);
		aTLine->SetLineWidth(3);
		//aTLine->SetLineColor(allGopts[i].colour);
		allTLines.push_back(aTLine);
	}
	return allTLines;
}


//TODO use fit_line
std::vector<std::vector<double>> fit_2lines(TGraphErrors* g, std::vector<double> fitRange){
	double l1_x1=fitRange[0]; double l1_x2=fitRange[1]; double l2_x1=fitRange[2]; double l2_x2=fitRange[3]; double curve_dx=fitRange[4];
	//define functions
	TF1* line1=new TF1("line1", "[0]*x+[1]", 0, 250);
	line1->SetParameters(1,1);
	TF1* line2=new TF1("line2", "[0]*x+[1]", 0, 250);
	line2->SetParameter(1,1);
	//prefit
	g->Fit("line1", "QW", "", l1_x1, l1_x2);
	g->Fit("line2", "QW", "", l2_x1, l2_x2);
	//first approximation of Vdep is from intersection of prefit functions
	//line1 y=mx+b
	//line1 y=k1x+b1
	//line2 has y=nx+c
	//line2 y=k2x+b2
	//intersection when c=mx+b -> x=(c-b)/m
	//intersection when k2x+b2=k1x+b1 -> x=(b2-b1)/(k1-k2)
	double k1 = line1->GetParameter(0);
	double b1 = line1->GetParameter(1);
	double k2 = line2->GetParameter(0);
	double b2 = line2->GetParameter(1);
	double intersectP[2] = {};
	intersectP[0] = (b2-b1)/(k1-k2);
	std::cout<<"prefit result k1 b1 k2 b2="<<k1<<" "<<b1<<" "<<k2<<" "<<b2<<", intersection point x "<<intersectP[0]<<"\n";
	
	//final fit
	//option M improves fit with TMinuit algorithm
	g->Fit("line1", "QM0", "", l1_x1, intersectP[0]-curve_dx/2);
	g->Fit("line2", "QM0+", "", intersectP[0]+curve_dx/2, l2_x2);
	//calculate and print Vdep from final fit
	k1 = line1->GetParameter(0);
	b1 = line1->GetParameter(1);
	k2 = line2->GetParameter(0);
	b2 = line2->GetParameter(1);
	//calculate error
	double k1Err = line1->GetParError(0);
	double b1Err = line1->GetParError(1);
	double k2Err = line2->GetParError(0);
	double b2Err = line2->GetParError(1);
	std::cout<<"final fit result k1 b1 k2 b2="<<k1<<" "<<b1<<" "<<k2<<" "<<b2<<"\n";
	std::cout<<"error of k1 b1 k2 b2="<<k1Err<<" "<<b1Err<<" "<<k2Err<<" "<<b2Err<<"\n";

	std::vector<double> fitRes1={k1,b1,k1Err,b1Err};
	std::vector<double> fitRes2={k2,b2,k2Err,b2Err};
	std::vector<std::vector<double>> fit_result={fitRes1,fitRes2};
	return fit_result;
} 


// fit 2 lines for 1/C^2 plot from points
std::vector<std::vector<double>> fit_2lines(TGraphErrors* g, std::vector<int> fitPoints={2,2,6,6,2}){
	// set default values of fitting range and curvewidth
	int l1_p1 = fitPoints[0];//nof points cut from beginning of g	
	int l2_p2 = fitPoints[1];//nof points cut from end of g
	int l1_n = fitPoints[2];//nof points used from beginning of cut g
	int l2_n = fitPoints[3];//nof points used from end of cut g
	int curve_n = fitPoints[4];//nof points in curve, cut from final fit
	double l1_x1 = g->GetPointX(l1_p1+1);
	double l1_x2 = g->GetPointX(l1_p1+l1_n+1);
	double l2_x1 = g->GetPointX(g->GetN()-l2_p2-l2_n);
	double l2_x2 = g->GetPointX(g->GetN()-l2_p2-1);
	double curve_dx = (g->GetPointX(l1_p1+1)-g->GetPointX(l1_p1))*curve_n;
	std::vector<double> fitRange={l1_x1, l1_x2, l2_x1, l2_x2, curve_dx};
	std::vector<std::vector<double>> fit_result=fit_2lines(g, fitRange);
	//also add the x values
	fit_result[0].push_back(l1_x1);
	fit_result[0].push_back(l1_x2);
	fit_result[1].push_back(l2_x1);
	fit_result[1].push_back(l2_x2);
	return fit_result;
}


std::vector<double> calc_Intersection(std::vector<std::vector<double>> fitRes){
	std::vector<double> intersectionP;
	double k1=fitRes[0][0];
	double b1=fitRes[0][1];
	double k1_err=fitRes[0][2];
	double b1_err=fitRes[0][3];

	double k2=fitRes[1][0];
	double b2=fitRes[1][1];
	double k2_err=fitRes[1][2];
	double b2_err=fitRes[1][3];

	double x=(b2-b1)/(k1-k2);
	double y=k1*x+b1;
	intersectionP.push_back(x);
	intersectionP.push_back(y);

	//check expression below? TODO
	double x_err = sqrt(pow(k1_err*(b2-b1)/((k1-k2)*(k1-k2)),2) + sqrt(pow(k2_err*(b2-b1)/((k1-k2)*(k1-k2)),2)) + pow(b1_err/(k1-k2), 2) + pow(b2_err/(k1-k2), 2));
	intersectionP.push_back(x_err);
	return intersectionP;
}


std::vector<TLine*> addFit_CV_TLine(std::vector<TGraphErrors*> allGs, std::vector<TGE> &allGopts, std::vector<std::vector<int>> allFitPoints){
	std::vector<TLine*> allTLines;
	for (int i=0;i<allGs.size();i++){
		std::vector<std::vector<double>> fitRes=fit_2lines(allGs[i], allFitPoints[i]);
		std::vector<double> Vdep_result=calc_Intersection(fitRes);
		double Vdep    =Vdep_result[0];
		double Vdep_unc=Vdep_result[2];

		// round Vdep and add to legend
		std::string VdepStr=roundToStr(Vdep,1);
		allGopts[i].legend=allGopts[i].legend+" "+TString(VdepStr);

		//draw TLine
		double k1=fitRes[0][0];
		double b1=fitRes[0][1];
		double k1_err=fitRes[0][2];
		double b1_err=fitRes[0][3];

		double k2=fitRes[1][0];
		double b2=fitRes[1][1];
		double k2_err=fitRes[1][2];
		double b2_err=fitRes[1][3];
		std::cout<<"k1, b1, k2, b2, Vdep, legend: ";
		std::cout<<"k1="<<k1<<"+-"<<k1_err<<" b1="<<b1<<"+-"<<b1_err<<"k2="<<k2<<"+-"<<k2_err<<" b2="<<b2<<"+-"<<b2_err<<" Vdep="<<Vdep<<"+-"<<Vdep_unc<<"V, legend: "<<allGopts[i].legend<<"\n";

		double x1=fitRes[0][4];
		double y1=k1*x1+b1;
		//double y1=theGraphToFit->GetPointY(l1_p1+1);
		double x2=Vdep;
		double y2=k1*x2+b1;
		double x3=fitRes[1][5];
		double y3=k2*x3+b2;
		//std::cout<<"x1, y1, x2, y2: "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<"\n";
		TLine* line1 =new TLine(x1, y1, x2, y2);
		//std::cout<<"line width: !!!!!!"<<(line1->GetLineWidth())<<"\n";
		line1->SetLineColor(allGopts[i].colour);
		line1->SetLineWidth(allGopts[i].lineWidth);
		allTLines.push_back(line1);
		TLine* line2=new TLine(x2, y2, x3, y3);
		line2->SetLineColor(allGopts[i].colour);
		line2->SetLineWidth(allGopts[i].lineWidth);
		allTLines.push_back(line2);
	}
	return allTLines;
}
