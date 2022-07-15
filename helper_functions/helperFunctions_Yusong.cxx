

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
	/*
	for (int i=0;i<theVector.size();i++){
		std::cout<<theVector[i]<<" ";
	}
	std::cout<<"\n";
	*/
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
		//std::cout<<"in for loop, i: "<<i<<"\n";
		if (theVector[i]==theString){
			//std::cout<<"in if, theVector[i]: "<<theVector[i]<<"\n";
			indexOfElement=i;
			break;
		}
	}
	//std::cout<<"Exiting findItemInVector, indexOfElement: "<<indexOfElement<<", the string looking for: "<<theString<<", i: "<<i<<"\n";
	return indexOfElement;
}


int findItemInVector(std::vector<TString> theVector, std::string theString){
	//std::cout<<"This is the findItemInVector for TString!\n";
	int indexOfElement=-1; int i=0;
	for (i;i<theVector.size();i++){
		if (theVector[i]==theString){
			indexOfElement=i;
			break;
		}
	}
	//std::cout<<indexOfElement<<": "<<theString<<" <- indexOfElement, i: "<<i<<"\n";
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
	return existOrNot;
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
		//printVectorVector(allTests);//this worked
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
	TString legend="";
	TString drawOption="";
	double minX=-999;
	double maxX=-999;
	double minY=-999;
	double maxY=-999;
	int whichTPad=1;
	double minXaxis;
	double maxXaxis;
	double minYaxis;
	double maxYaxis;
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
	//std::cout<<"have "<<theDataVec[0].size()<<"points!\n";
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
	TString title="canvas title";
	TString Xaxis="X";
	TString Yaxis="Y";
	int width=900;
	int height=600;
	std::string inputFolder="";
	std::string outputFolder="";
	std::vector<std::string> fileNames={""};//input files that contains data
	std::vector<std::string> legendEntries={""};
	bool saveAfterCorrection=1;
	std::vector<std::string> figFileName={"figureFileName"};
	std::vector<std::string> figFileFormats={"png"};
	std::vector<int> colours={kBlack, kRed, kGreen, kBlue, kYellow, kMagenta, kCyan, 12, kOrange-3, kSpring-6, kAzure-6, kViolet+1};
	std::vector<int> markers={20, 21, 22, 23, 20, 21, 22, 23, 33, 34, 29, 43, 24, 25, 26, 32, 27, 28, 30, 42};
	std::vector<int> TPadColours={1,861};//860 is kAzure
	TString drawOption="";//useful?
	double minX=-999;
	double maxX=-999;
	double minY=-999;
	double maxY=-999;
	double minXaxis;
	double maxXaxis;
	double minYaxis;
	double maxYaxis;
	std::vector<double> offsetsX={0.};
	std::vector<double> offsetsY={0.};
	std::vector<double> coefficientsX={1.};
	std::vector<double> coefficientsY={1.};

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


double calcFluctuation(std::vector<double> Yvec){
	//print out the fluctuation
	double theMin=findMinMaxAvg(Yvec,"min");
	double theMax=findMinMaxAvg(Yvec,"max");
	double theAvg=findMinMaxAvg(Yvec,"avg");
	double thePerc=(theMax-theMin)/theAvg*100;
	std::cout<<"minimum: "<<theMin<<" maximum: "<<theMax<<" average: "<<theAvg/*<<" temperature in K is :"<<Xvec*/<<" (max-min)/avg[%]: "<<thePerc<<"!!!\n\n";
	return thePerc;
}


std::vector<double> retAxisRange(TGraphErrors* &theTGE){
	double xmin = theTGE->GetXaxis()->GetXmin();
	double xmax = theTGE->GetXaxis()->GetXmax();
	double ymin = theTGE->GetYaxis()->GetXmin();//GetYmin() does not exist
	double ymax = theTGE->GetYaxis()->GetXmax();//GetYmax() does not exist
	std::vector<double> theRange={xmin, xmax, ymin, ymax};
	return theRange;
}


void fillTGEaxisRange(TGraphErrors* &theTGE, TGEoptions &theTGEoptions){
	std::vector<double> theRange=retAxisRange(theTGE);
	theTGEoptions.minXaxis=theRange[0];
	theTGEoptions.maxXaxis=theRange[1];
	theTGEoptions.minYaxis=theRange[2];
	theTGEoptions.maxYaxis=theRange[3];
	std::cout<<"The axis range for this TGraphErrors: "<<theTGEoptions.minXaxis<<" "<<theTGEoptions.maxXaxis<<" "<<theTGEoptions.minYaxis<<" "<<theTGEoptions.maxYaxis<<"\n";
}


void fillCanAxisRange(std::vector<TGraphErrors*> &allTheTGEs, canOptions &theCanOpts){//std::vector<TGEoptions> &theTGEoptions){
	std::cout<<"# of graphs to be drawn on pad2 (allTheTGEs.size()): "<<allTheTGEs.size()<<"\n";
	std::vector <std::vector<double>> allRanges;
	std::vector<double> theRange;
	for (int i=0;i<allTheTGEs.size();i++){
		theRange=retAxisRange(allTheTGEs[i]);
		printVector(theRange,"the range: ");
		allRanges.push_back(theRange);
	}
	std::vector<double> minXaxes;
	std::vector<double> maxXaxes;
	std::vector<double> minYaxes;
	std::vector<double> maxYaxes;
	std::cout<<"!!!!!! how many ranges to be taken into consideration: "<<allRanges.size()<<"\n";
	for (int i=1;i<allRanges.size();i++){
		minXaxes.push_back(allRanges[i][0]);
		maxXaxes.push_back(allRanges[i][1]);
		minYaxes.push_back(allRanges[i][2]);
		maxYaxes.push_back(allRanges[i][3]);
	}
	//find the min of the mins and the max of the maxes
	theCanOpts.minXaxis=findMinMaxAvg(minXaxes,"min");
	theCanOpts.maxXaxis=findMinMaxAvg(maxXaxes,"max");
	theCanOpts.minYaxis=findMinMaxAvg(minYaxes,"min");
	theCanOpts.maxYaxis=findMinMaxAvg(maxYaxes,"max");
	std::cout<<"The axis range for this TGraphErrors: "<<theCanOpts.minXaxis<<" "<<theCanOpts.maxXaxis<<" "<<theCanOpts.minYaxis<<" "<<theCanOpts.maxYaxis<<"\n";
}


//parameters needed: allGraphs, allTGEopts, can
void drawTGEsOnCanvas(TCanvas* can, TLegend* canLeg, std::vector<TGraphErrors*> allGraphs, std::vector<TGEoptions> allTGEopts, TPad* theTPad){
	for (int i=0;i<allGraphs.size();i++){
		can->cd();
		//theTPad->SetRightMargin(0.3);
		//allGraphs[i]->Print();//for debugging, prints out the data
		theTPad->Draw();
		theTPad->cd();
		TString theDrawOption=allTGEopts[i].drawOption;
		allGraphs[i]->Draw(theDrawOption+" same");
		canLeg->AddEntry(allGraphs[i], allTGEopts[i].legend, theDrawOption);
		gPad->Update();
	}
}


TCanvas* plotGraphsOnCanvas(std::vector<TGraphErrors*> allGraphs, canOptions &canOpts, std::vector<TGEoptions> allTGEopts){
	printVector(canOpts.figFileName,"The figure(s) will be saved under this name: ");
	printVector(canOpts.figFileFormats,"The figure(s) will be saved in these formats: ");
	gStyle->SetOptTitle(0); 
	TGaxis::SetMaxDigits(3);
	TCanvas* can = new TCanvas(canOpts.title,canOpts.title+"_name", canOpts.width, canOpts.height);
	TPad* pad1 = new TPad("pad1", "", 0, 0, 1, 1);
	pad1->SetGrid();
	double x1;double y1;double x2;double y2;
	//pad1->GetRange(x1, y1, x2, y2);
	//std::cout<<"Initial pad1->GetRange:\n"<<x1<<" "<<x2<<" "<<y1<<" "<<y2<<"\n";
	TLegend* canLeg=new TLegend(0.72,0.1,0.98,0.9);
	//canLeg->SetHeader("The Legend Title","C");

	TGraph* dummy=dummyGraph(canOpts.minX,canOpts.maxX, canOpts.minY,canOpts.maxY, canOpts.title);
	dummy->GetXaxis()->SetTitle(canOpts.Xaxis);
	dummy->GetYaxis()->SetTitle(canOpts.Yaxis);
	//dummy->GetYaxis()->SetTitleOffset(1.1);
	can->cd();
	pad1->SetRightMargin(0.3);
	pad1->Draw();
	pad1->cd();
	dummy->Draw(canOpts.drawOption);

	//tell how many TPads needed
	std::cout<<"# of graphs to be drawn: "<<allGraphs.size()<<"\n";
	bool need2Pads=false;
	std::vector<TGraphErrors*> allGraphs2;
	std::vector<TGEoptions> allTGEopts2;
	if (allGraphs.size()!=0){
		for (int i=allGraphs.size()-1;i>=0;i--){
			if (allTGEopts[i].whichTPad!=1){
				need2Pads=true;
				allGraphs2.push_back(allGraphs[i]);
				allTGEopts2.push_back(allTGEopts[i]);
				allGraphs.erase(allGraphs.begin()+i);
				allTGEopts.erase(allTGEopts.begin()+i);
			}
		}
	}
	std::cout<<"# of graphs to be drawn: "<<allGraphs.size()<<"\n";
	//draw all graphs (now only left those that should be drawn on pad1) on canvas
	drawTGEsOnCanvas(can, canLeg, allGraphs, allTGEopts, pad1);
	pad1->GetRange(x1, y1, x2, y2);
	std::cout<<"pad1->GetRange:\n"<<x1<<" "<<x2<<" "<<y1<<" "<<y2<<"\n";
	TPad* pad2;
	if (need2Pads){
		pad2 = new TPad("pad2", "", x1, y1, x2, y2);
		pad2->SetFillStyle(4000);

		//pad2->SetRightMargin(0.3);
		//pad2->Draw();
		canOptions canOpts2;
		std::cout<<"# of graphs to be drawn on pad2: "<<allGraphs2.size()<<"\n";
		fillCanAxisRange(allGraphs2,canOpts2);
		double dx = (canOpts2.maxXaxis - canOpts2.minXaxis);
		double dy = (canOpts2.maxYaxis - canOpts2.minYaxis);
		pad2->Range(canOpts2.minXaxis,canOpts2.minYaxis,canOpts2.maxXaxis,canOpts2.maxYaxis);
		//pad2->Range(canOpts2.minXaxis-0.2*dx,canOpts2.minYaxis-0.2*dy,canOpts2.maxXaxis+0.2*dx,canOpts2.maxYaxis+0.2*dy);
		pad2->GetRange(x1, y1, x2, y2);
		std::cout<<"pad2->GetRange:\n"<<x1<<" "<<x2<<" "<<y1<<" "<<y2<<"\n";
		//pad2->SetPad(x1, y1, x2, y2);
		drawTGEsOnCanvas(can, canLeg, allGraphs2, allTGEopts2, pad2);
		/*
		TGaxis *xaxis = new TGaxis(canOpts2.minXaxis, canOpts2.maxYaxis, canOpts2.maxXaxis, canOpts2.maxYaxis, canOpts2.minXaxis, canOpts2.maxXaxis, 5, "-L");
		xaxis->SetLineColor(kRed);
		xaxis->SetLabelColor(kRed);
		xaxis->Draw();
		gPad->Update();
		*/
		
		TGaxis* yaxis = new TGaxis(canOpts2.maxXaxis, canOpts2.minYaxis, canOpts2.maxXaxis, canOpts2.maxYaxis, canOpts2.minYaxis, canOpts2.maxYaxis, 5, "-L");
		yaxis->SetLineColor(kRed);
		yaxis->SetLabelColor(kRed);
		yaxis->Draw();
		gPad->Update();
		
	}

	canLeg->SetBorderSize(0);//gets rid of the black boarder around the legend
	canLeg->SetFillColor(0);
	gPad->Update();//pad1->Update();//does not work?
	canLeg->Draw();
	can->Show();


	// save the figure
	// a list of available formats can save in. If what was specified is available, save in this format. If not, say it
	std::vector<std::string> availableFormats={"png","pdf"};
	if (canOpts.figFileName[0]!=""){
		for (int i=0;i<(canOpts.figFileFormats).size();i++){
			int theFoundIndex=findItemInVector(availableFormats,canOpts.figFileFormats[i]);
			//std::cout<<"!!! "<<i<<" the found index: "<<theFoundIndex<<"\n";
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


