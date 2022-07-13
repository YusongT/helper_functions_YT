

//prints 1D vector in std::string
//printVector(theDataPoints[0],"vector theDataPoints[0]: \n");
void printVector(std::vector<std::string> theVector, std::string theString=""){
	if (theString!=""){
		std::cout<<theString;
	}
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
		std::cout<<"has length 0!\n";
	}
}


// prints 1D vector in double
void printVector(std::vector<double> theVector, std::string theString=""){
	if (theString!=""){
		std::cout<<theString;
	}
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
		std::cout<<"has length 0!\n";
	}
}


// prints 2D vector in std::string, used in getData
// uses printVector
//printVector(theDataPoints[0],"vector theDataPoints[0]: \n");
void printVectorVector(std::vector<std::vector<std::string>> theVector, std::string theString=""){
	if (theString!=""){
		std::cout<<theString;
	}
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


// finds a string element in an string vector
int findItemInVector(std::vector<std::string> theVector, std::string theString){
	//std::cout<<"This is the findItemInVector for string! Finding string \""<<theString<<"\"\n";
	int indexOfElement=-1; int i=0;
	for (i;i<theVector.size();i++){
		std::cout<<"in for loop, i: "<<i<<"\n";
		if (theVector[i]==theString){
			std::cout<<"in if, theVector[i]: "<<theVector[i]<<"\n";
			indexOfElement=i;
			break;
		}
	}
	//std::cout<<"Exiting findItemInVector, indexOfElement: "<<indexOfElement<<", the string looking for: "<<theString<<", i: "<<i<<"\n";
	return indexOfElement;
}


int findItemInVector(std::vector<TString> theVector, std::string theString){
	std::cout<<"This is the findItemInVector for TString!\n";
	int indexOfElement=-1; int i=0;
	for (i;i<theVector.size();i++){
		if (theVector[i]==theString){
			indexOfElement=i;
			break;
		}
		std::cout<<theVector[indexOfElement]<<"\n";
	}
	std::cout<<indexOfElement<<": "<<theString<<" <- indexOfElement, i: "<<i<<"\n";
	return indexOfElement;
}


double findMinMaxAvg(std::vector<double> theVector, std::string theString=""){
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


void fileExistsOrNot(TString fileName, TString inputPath = ""){
	std::ifstream ifile;
	std::cout<<inputPath<<fileName<<" ";
	ifile.open(inputPath+fileName);
	if(ifile) {
		std::cout<<"file exists\n";
	} else {
		std::cout<<"file doesn't exist\n";
	}
}


void addFolderToFile(std::string folderName, std::vector<std::string> &fileNameVec){
	for (int i=0;i<fileNameVec.size();i++){
		fileNameVec[i]=folderName+fileNameVec[i];
		fileExistsOrNot(fileNameVec[i]);
	}
}


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
	/*
	for (int i=0;i<theVector.size();i++){
		std::cout<<theVector[i]<<" ";
	}
	std::cout<<"\n";
	*/
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
		printVectorVector(allTests);//this worked
	}
	return allTests;
}


// takes the resulting 2D vector "alltests" from getData
// puts the particular column (from certain row, take one element from each element (which is a vector) of allTests) in a vector
// when counting the column and row numbers, count from 0
std::vector<double> getDataVector(std::vector<std::vector<std::string>> &theData, int nthColumn, int labelsRow=-1, double correctionVal=0., double coefficient=1., int selCriteriaColumn=-1, double selCriteria=-999){
	std::vector<double> theVector;
	//printVectorVector(theData);
	for(int i=labelsRow+1;i<(theData.size());i++){
		double theNumber=atof((theData[i][nthColumn]).c_str());
		theVector.push_back((theNumber+correctionVal)*coefficient);
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


class TGEoptions{
	public:
	int colour=8;
	float markerSize=1;
	int markerStyle=8;
	std::string legend="";
	void setValues(int theColour, float theMarkerSize, int theMarkerStyle, std::string theLegend){
		colour=theColour; 
		markerSize=theMarkerSize;
		markerStyle=theMarkerStyle;
		legend=theLegend;
	}
};


TGraphErrors* makeTGraphErrors(std::vector<std::vector<double>> &theDataVec, TGEoptions &theOptions){
	TGraphErrors* theTGraphErrors=new TGraphErrors;
	int theNthPoint=0;
	std::cout<<"have "<<theDataVec[0].size()<<"points!\n";
	for (int i=0;i<theDataVec[0].size();i++){
		theTGraphErrors->SetPoint(theNthPoint,theDataVec[0][i],theDataVec[1][i]);
		if(theDataVec.size()==3){
			theTGraphErrors->SetPointError(theNthPoint,0.,theDataVec[2][i]);
		}
		theNthPoint=theNthPoint+1;
	}
	if (theDataVec.size()==4){
		std::cout<<"have uncertainty!\n";
	}
	theTGraphErrors->SetMarkerColor(theOptions.colour);
	//std::cout<<"marker colour set! "<<theOptions.colour<<"\n";
	theTGraphErrors->SetMarkerSize(theOptions.markerSize);
	theTGraphErrors->SetLineColor(theOptions.colour);
	theTGraphErrors->SetLineWidth(2);
	theTGraphErrors->SetMarkerStyle(theOptions.markerStyle);
	return theTGraphErrors;
}


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


class canOptions{
	public:
	double minX=-999;
	double maxX=-999;
	double minY=-999;
	double maxY=-999;
	TString title="canvas title";
	TString Xaxis="X";
	TString Yaxis="Y";
	TString drawOption="";
	int width=900;
	int height=600;
	std::vector<std::string> figFileName={"figureFileName"};
	std::vector<std::string> figFileFormats={"png"};
	std::string outputFolder="";
	std::string inputFolder="";
	std::vector<std::string> fileNames={""};
	std::vector<std::string> legendEntries={""};
	std::vector<int> colours={kBlack, kRed, kGreen, kBlue, kYellow, kMagenta, kCyan, 12, kOrange-3, kSpring-6, kAzure-6, kViolet+1};
	std::vector<int> markers={20, 21, 22, 23, 20, 21, 22, 23, 33, 34, 29, 43, 24, 25, 26, 32, 27, 28, 30, 42};
	std::vector<double> offsetsX={0.};
	std::vector<double> offsetsY={0.};
	std::vector<double> coefficientsX={1.};
	std::vector<double> coefficientsY={1.};
	bool saveAfterCorrection=1;
	TGaxis* secondAxis=nullptr;

	void setValues(double theMinX, double theMaxX, double theMinY, double theMaxY, TString theTitle, TString theXaxis, TString theYaxis, TString theDrawOpt="", int theWidth=900, int theHeight=600){
		Xaxis=theXaxis; Yaxis=theYaxis; title=theTitle;
		minX=theMinX; maxX=theMaxX; minY=theMinY; maxY=theMaxY;
		drawOption=theDrawOpt;
		width=theWidth; height=theHeight;
	}
};


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


std::vector<double> convertTo1overY2(std::vector<double> Y, double multiplyX=1., double multiplyY=1.){
	std::vector<double> oneOverY2;
	for(int i=0; i<Y.size(); i++){
		oneOverY2.push_back(1./(Y[i]*Y[i]));
	}
	return oneOverY2;
}


TCanvas* plotGraphsOnCanvas(std::vector<TGraphErrors*> allGraphs, std::vector<TString> allLegends, canOptions &canOpts, std::vector<TString> drawOpts){
	printVector(canOpts.figFileName,"The figure(s) will be saved under this name: ");
	printVector(canOpts.figFileFormats,"The figure(s) will be saved in these formats: ");
	gStyle->SetOptTitle(0); 
	TGaxis::SetMaxDigits(3);
	TCanvas* can = new TCanvas(canOpts.title,canOpts.title+"_name", canOpts.width, canOpts.height);
	gPad->SetRightMargin(0.3);
	TLegend* canLeg=new TLegend(0.72,0.1,0.98,0.9);
	//canLeg->SetHeader("The Legend Title","C");

	TGraph* dummy=dummyGraph(canOpts.minX,canOpts.maxX, canOpts.minY,canOpts.maxY, canOpts.title);
	dummy->GetXaxis()->SetTitle(canOpts.Xaxis);
	dummy->GetYaxis()->SetTitle(canOpts.Yaxis);
	//dummy->GetYaxis()->SetTitleOffset(1.1);
	can->cd();
	dummy->Draw(canOpts.drawOption);
	std::cout<<allGraphs.size()<<"\n";
	for (int i=0;i<allGraphs.size();i++){
		std::cout<<drawOpts[i]<<"\n";
		can->cd();
		allGraphs[i]->Print();
		allGraphs[i]->Draw(drawOpts[i]+" same");
		canLeg->AddEntry(allGraphs[i], allLegends[i], drawOpts[i]);
	}

	canLeg->SetBorderSize(0);//gets rid of the black boarder around the legend
	canLeg->SetFillColor(0);
	gPad->Update();
	canLeg->Draw();
	if (canOpts.secondAxis!=nullptr){
		(canOpts.secondAxis)->Draw();
	}
	can->Show();

	// save the figure
	// a list of available formats can save in. If what was specified is available, save in this format. If not, say it
	std::vector<std::string> availableFormats={"png","pdf"};
	if (canOpts.figFileName[0]!=""){
		for (int i=0;i<(canOpts.figFileFormats).size();i++){
			int theFoundIndex=findItemInVector(availableFormats,canOpts.figFileFormats[i]);
			std::cout<<"!!! "<<i<<" the found index: "<<theFoundIndex<<"\n";
			if ((theFoundIndex)!=-1){
				TString outputFileName=canOpts.outputFolder+canOpts.figFileName[0]+"."+canOpts.figFileFormats[i];
				can->Print(outputFileName);
			}else{
				std::cout<<"specified format \""<<canOpts.figFileFormats[i]<<"\" not available! Please use all lower case letters, if haven't done so already\n";
			}
		}
	}
	return can;
}


