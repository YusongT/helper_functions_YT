

void printString(std::string theString, std::string anotherString=""){
	//std::cout<<"function started!\n";
	if (theString!=""){
		std::cout<<theString<<anotherString;
	}
	//std::cout<<"function ended!\n";
}


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


// prints 1D vector in double
void printVector(std::vector<double> theVector, std::string theString=""){
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


void expandVector(std::vector<double> &theVector, int theSize, int whichToRepeat=0, std::string toPrint=""){
	//std::cout<<"in expandVector! Size of vector to expand: "<<theVector.size()<<"\n";
	//printVector(theVector);
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


//Define a function to output a vector of vectors of strings as a .txt file
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


std::string roundToStr(float theNum, int nofDigit){
	std::stringstream strStream;
	strStream << std::fixed << std::setprecision(nofDigit) << theNum;
	std::string s = strStream.str();
	return s;
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
		printVectorVector(allTests);
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
	TString drawOption="lp";
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


// functions that use canOptions must be written below this class definition of canOptions
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
	int indexRow=-1;
	int indexColX=-1;
	int indexColY=-1;
	int indexColXunc=-1;
	int indexColYunc=-1;
	std::string plotType="";

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
	TString drawOption="lp";//useful?

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
	std::vector<double> coefficientsX={1.};
	std::vector<double> coefficientsY={1.};

	void setValues(double theMinX, double theMaxX, double theMinY, double theMaxY, TString theTitle, TString theXaxis, TString theYaxis, TString theDrawOpt="", int theWidth=900, int theHeight=600){
		Xaxis=theXaxis; Yaxis=theYaxis; title=theTitle;
		minX=theMinX; maxX=theMaxX; minY=theMinY; maxY=theMaxY;
		drawOption=theDrawOpt;
		width=theWidth; height=theHeight;
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


std::vector<double> convertTo1overY2(std::vector<double> Y, double multiplyX=1., double multiplyY=1.){
	std::vector<double> oneOverY2;
	for(int i=0; i<Y.size(); i++){
		oneOverY2.push_back(1./(Y[i]*Y[i]));
	}
	return oneOverY2;
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


std::vector<double> retAxisRange(TGraphErrors* &theTGE){
	double xmin = theTGE->GetXaxis()->GetXmin();
	double xmax = theTGE->GetXaxis()->GetXmax();
	double ymin = theTGE->GetYaxis()->GetXmin();//GetYmin() does not exist
	double ymax = theTGE->GetYaxis()->GetXmax();//GetYmax() does not exist
	std::vector<double> theRange={xmin, xmax, ymin, ymax};
	return theRange;
}


void fillTGEaxisRange(TGraphErrors* &theTGE, TGEoptions &theTGEoptions){
	std::cout<<"in fillTGEaxisRange\n";
	std::vector<double> theRange=retAxisRange(theTGE);
	theTGEoptions.minXval=theRange[0];
	theTGEoptions.maxXval=theRange[1];
	theTGEoptions.minYval=theRange[2];
	theTGEoptions.maxYval=theRange[3];
	std::cout<<"The axis range for this TGraphErrors: "<<theTGEoptions.minXval<<" "<<theTGEoptions.maxXval<<" "<<theTGEoptions.minYval<<" "<<theTGEoptions.maxYval<<"\n";
}


// finds the min and max of X and Y in alltheTGEs, and fill them into theCanOpts.minXval, maxXval, minYval, maxYval
void fillCanAxisRange(std::vector<TGraphErrors*> &allTheTGEs, canOptions &theCanOpts){//std::vector<TGEoptions> &theTGEoptions){
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




TCanvas* initCan(canOptions canOpts, TPad* &pad0, TPad* &pad1){
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
	pad1->Draw();
	pad1->SetGrid();
	//pad1->SetFillColor(kYellow-7);//393
	//double x1;double y1;double x2;double y2;
	//pad1->GetRange(x1, y1, x2, y2);
	//std::cout<<"Initial pad1->GetRange:\n"<<x1<<" "<<x2<<" "<<y1<<" "<<y2<<"\n";//0 1 0 1
	TGraph* dummy=dummyGraph(canOpts.minX,canOpts.maxX, canOpts.minY,canOpts.maxY, canOpts.title);
	//std::cout<<"canOpts extremes: "<<canOpts.minX<<" "<<canOpts.maxX<<" "<<canOpts.minY<<" "<<canOpts.maxY<<"\n";
	dummy->GetXaxis()->SetTitle(canOpts.Xaxis);
	dummy->GetXaxis()->SetTitleOffset(1.1);
	dummy->GetXaxis()->SetLabelSize(canOpts.xLabelSize);
	dummy->GetXaxis()->SetTitleSize(canOpts.xLabelSize);
	//std::cout<<"canOpts.xLabelSize: "<<canOpts.xLabelSize<<"\n";
	dummy->GetYaxis()->SetTitle(canOpts.Yaxis);
	dummy->GetYaxis()->SetTitleOffset(1.25);
	dummy->GetYaxis()->SetLabelSize(canOpts.yLabelSize);
	dummy->GetYaxis()->SetTitleSize(canOpts.yLabelSize);
	pad1->cd();
	dummy->Draw("ap");// this must be "ap" // pad1 range still 0 1 0 1
	//dummy->Draw(canOpts.drawOption);// pad1 range still 0 1 0 1
	//std::cout<<canOpts.drawOption<<endl;
	return can;
}


//parameters needed: allGraphs, allTGEopts, can
//adds entry to legend
// how to draw two axes: https://root-forum.cern.ch/t/draw-two-graphs-on-one-canvas-with-different-y-scales/21755/6
// a good intro about TPad https://root.cern.ch/root/html534/guides/users-guide/Graphics.html
TCanvas* putGraphsOnCanvas(TCanvas* &can, TLegend* &canLeg, canOptions &canOpts, std::vector<TGraphErrors*> allGraphs, std::vector<TGEoptions> allTGEopts, TPad* &theTPad){
	std::cout<<"total # of graphs to be drawn: "<<allGraphs.size()<<"\n";
	can->cd();
	theTPad->Draw();
	theTPad->cd();
	for (int i=0;i<allGraphs.size();i++){
		TString theDrawOption=allTGEopts[i].drawOption;
		//allGraphs[i]->Print();//for debugging, prints out the data
		allGraphs[i]->Draw(theDrawOption+" same");
		canLeg->AddEntry(allGraphs[i], allTGEopts[i].legend, theDrawOption);
		//std::cout<<theDrawOption+" same"<<endl;
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


// range of new TPad initialised according to the exiting TPad
void initNewTPad(TCanvas* &can, TLegend* &canLeg, canOptions &canOpts2, std::vector<TGraphErrors*> allGraphs2, std::vector<TGEoptions> allTGEopts2, TPad* &pad2, TPad* pad1){
	//can->cd();// without this, pad2 has size same as pad1 even if used 0., 0., 1.0, 1.0
	std::cout<<"# of graphs to be drawn on pad2: "<<allGraphs2.size()<<"\n";
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
	int extraY=(canOpts2.maxYval-canOpts2.minYval)/2;
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
	float add1st=0.5;
	moveDown=moveDown*((idx+1)+add1st)*yRange;
	std::cout<<"!!! !!! idx: "<<idx<<" moveDown: "<<moveDown<<"\n";
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
	printVector(canOpts.figFileName,"The figure(s) will be saved under this name: ");
	printVector(canOpts.figFileFormats,"The figure(s) will be saved in these formats: ");
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
}


