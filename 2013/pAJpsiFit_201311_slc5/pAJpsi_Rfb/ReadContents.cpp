#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <stdlib.h>

using namespace std;

// Define which y, pT, cent bins are going to be used
// The order of elements will be kept in the final results!

// --------- Rapidity - Array Ordering from forward to backward !

////// for Pbp
//string str_rap[] = {"-2.4-1.46"}; //y integ
//static string str_rap[] = {"-2.4--0.47","-0.47-1.46"}; // rapcoarser
//static string str_rap[]={"-2.4--1.97", "-1.97--1.72", "-1.72--1.47", "-1.47--1.22", "-1.22--0.97", "-0.97--0.72", "-0.72--0.47", "-0.47--0.22", "-0.22-0.03", "0.03-0.28", "0.28-0.53", "0.53-0.78", "0.78-1.03", "1.03-1.46"}; // rapfiner3

////// for pPb
//string str_rap[] = {"-1.46-2.4"}; //y integ
//static string str_rap[] = {"0.47-2.4","-1.46-0.47"}; // rapcoarser
static string str_rap[] = {"1.97-2.4", "1.72-1.97", "1.47-1.72", "1.22-1.47", "0.97-1.22", "0.72-0.97", "0.47-0.72", "0.22-0.47", "-0.03-0.22", "-0.28--0.03", "-0.53--0.28", "-0.78--0.53", "-1.03--0.78", "-1.46--1.03"}; // rapfiner3

////// for pp
//static string str_rap[] = {"-1.93-0.00","0.00-1.93"}; // rapcoarser
//static string str_rap[] = {"-1.93--1.50", "-1.50--1.25", "-1.25--1.00", "-1.00--0.75", "-0.75--0.50", "-0.50--0.25", "-0.25-0.00", "0.00-0.25", "0.25-0.05", "0.05-0.75", "0.75-1.00", "1.00-1.25", "1.25-1.50", "1.50-1.93"}; // rapfiner3

// --------- pT

static string str_pt[] = {"6.5-30.0"}; //integ
//static string str_pt[]={"6.5-7.5", "7.5-8.5", "8.5-9.5", "9.5-10.5", "10.5-11.5", "11.5-12.5", "12.5-14.5", "14.5-16.5", "16.5-20.0", "20.0-30.0"};// ptfiner
//static string str_pt[]={"6.5-8.0", "8.0-10.0", "10.0-13.0", "13.0-30.0"}; //4bins
//static string str_pt[]={"6.5-7.5", "7.5-8.5", "8.5-9.5", "9.5-10.5" ,"10.5-11.5", "11.5-13.0", "13.0-16.0", "16.0-20.0", "20.0-30.0"};//9bins
//static string str_pt[]={"6.5-7.5", "7.5-8.5", "8.5-9.5", "9.5-11.0", "11.0-14.0", "14.0-30.0"}; //6bins

// --------- Centrality

static string str_cent[] = {"0.0-100.0"}; // also for pp
//static string str_cent[] = {"50-100", "30-50", "10-30", "0-10"};
//static string str_cent[] = {"70-100", "60-70", "50-60", "40-50", "30-40", "20-30", "10-20", "0-10"}; //KYO


static std::vector<string> rapidity(str_rap,str_rap+sizeof(str_rap)/sizeof(string));
static std::vector<string> pt(str_pt,str_pt+sizeof(str_pt)/sizeof(string));
static std::vector<string> centrality(str_cent,str_cent+sizeof(str_cent)/sizeof(string));
static const int nRap = sizeof(str_rap)/sizeof(string);
static const int nPt = sizeof(str_pt)/sizeof(string);
static const int nCent = sizeof(str_cent)/sizeof(string);

struct eachRow {
  string rap, pt, cent;
  double nsig, nsigerr, npr, nprerr, nnp, nnperr;
  eachRow():rap(str_rap[0]),pt(str_pt[0]),cent(str_cent[0]),nsig(1),nsigerr(0.1),npr(1),nprerr(0.1),nnp(1),nnperr(0.1){ };
};

bool ComparatorWithArray(eachRow data1, eachRow data2) {
  bool result;
 
  // Check item is in the comparison array 
  std::vector<string>::iterator locRap1 = find(rapidity.begin(),rapidity.end(),data1.rap);
  std::vector<string>::iterator locPt1 = find(pt.begin(),pt.end(),data1.pt);
  std::vector<string>::iterator locCent1 = find(centrality.begin(),centrality.end(),data1.cent);
  std::vector<string>::iterator locRap2 = find(rapidity.begin(),rapidity.end(),data2.rap);
  std::vector<string>::iterator locPt2 = find(pt.begin(),pt.end(),data2.pt);
  std::vector<string>::iterator locCent2 = find(centrality.begin(),centrality.end(),data2.cent);

  if ( (locRap1 == rapidity.end()) || (locPt1 == pt.end()) || (locCent1 == centrality.end()) ||
       (locRap2 == rapidity.end()) || (locPt2 == pt.end()) || (locCent2 == centrality.end()) ) {
    cerr << "ComparatorWithArray:: one of element isn't found in rapidity/pt/centrality array!" << std::endl;
    std::cout << "ComparatorWithArray:: one of element isn't found in rapidity/pt/centrality array!" << std::endl;
    return false;
  }

  // Check found item's index number
  int idxRap1 = distance(rapidity.begin(), locRap1);
  int idxPt1 = distance(pt.begin(), locPt1); 
  int idxCent1 = distance(centrality.begin(), locCent1);
  int idxRap2 = distance(rapidity.begin(), locRap2);
  int idxPt2 = distance(pt.begin(), locPt2); 
  int idxCent2 = distance(centrality.begin(), locCent2);

  // Compare 2 items
  if (idxRap1 < idxRap2) {
    result = true;
  } else if ((idxRap1 == idxRap2) && (idxPt1 < idxPt2)) {
    result = true;
  } else if ((idxRap1 == idxRap2) && (idxPt1 == idxPt2) && (idxCent1 < idxCent2)) {
    result = true;
  } else {
    result = false;
  }

  return result;
};

bool CheckSameEntries(eachRow data1, eachRow data2) {
  // Compare 2 items in the list
  bool result;
  if (data1.rap == data2.rap && data1.pt == data2.pt && data1.cent == data2.cent) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

bool FindMissingElement(std::list<eachRow> data) {
  if (nRap*nPt*nCent != data.size()) {
    std::cout << "Data size: " << data.size() << "\tReference size: " << nRap*nPt*nCent << std::endl;
    
    std::list<string> existData, reference;  // rap, pt, cent
    std::list<string>::iterator it;
    std::list<eachRow>::iterator it_eachRow;

    for (int i=0; i<nRap; i++) {
      for (int j=0; j<nPt; j++) {
        for (int k=0; k<nCent; k++) {
          reference.push_back(rapidity[i] + "_" + pt[j] + "_" + centrality[k]);
        }
      }
    } // Fill up a list with required bins
    
    for (it_eachRow=data.begin(); it_eachRow!=data.end(); it_eachRow++) {
      existData.push_back((*it_eachRow).rap +"_"+ (*it_eachRow).pt +"_"+ (*it_eachRow).cent);
    } // Fill up a list with data vector

    // Find same entries both on reference and data and remove those entries
    for (it = existData.begin(); it != existData.end(); it++) {
      reference.remove(*it);
    }

    // Prints out not-matched entries
    for (it = reference.begin(); it != reference.end(); it++) {
      std::cout << "FindMissingElement: " << (*it) << std::endl;
    }
    return true;
  } else false;
}

int main(int argc, char *argv[]) {
  // Read fit result summary file
  char *inputFile;
  if (argc > 1) inputFile = argv[1];
  else {
    std::cout << "./a.out [input file] [output file]" << std::endl;
    return -2;
  }
  fstream finput;
  finput.open(inputFile);
  if (!finput.good()) {
    std::cout << "Cannot open input file: " << inputFile << std::endl;
    return -1;
  }

  // Read input file's header, column names
  string title; // which dataset/fit method is used for this table?
  getline(finput,title);
  string colNameTmp; // 2nd line contains column names
  getline(finput,colNameTmp);
  istringstream iss(colNameTmp); // Get column names (-> split colName)
  std::vector<string> colName;
  while (iss) {
    string sub;    iss >> sub;
    colName.push_back(sub);
  }
  colName.pop_back(); // Removes the last \n character

  std::list<eachRow> dataValueUseful; // fit results (only useful bins)
  std::list<eachRow>::iterator it_eachRow;

  // Read all lines in the file and store results into the vector
  while (finput.good()) {
    // Read a row and parsing it
    string dataline;
    getline(finput,dataline);
    if (dataline.size() == 0) break;  // EOF reached
    istringstream datarow(dataline);
    
    std::vector<string> dataValue; // fit results in each element
    while (datarow) {
      string sub;    datarow >> sub;
      dataValue.push_back(sub);   // Read data 1 line
    }
    if (dataValue.back() == "\n") dataValue.pop_back(); // Removes the last \n character

    // Check this row is useful or not
    std::vector<string>::iterator irap, ipt, icent;
    irap = find(rapidity.begin(),rapidity.end(),dataValue[0]);
    ipt = find(pt.begin(),pt.end(),dataValue[1]);
    icent = find(centrality.begin(),centrality.end(),dataValue[2]);

    //4,5(NSig,NSigErr), 8,9(PROMPT, PROMPTErr), 10,11(NON-PROMPT, NON-PROMPTErr)
    if (irap != rapidity.end() && ipt != pt.end() && icent != centrality.end()) {
      eachRow data;
      data.rap = dataValue[0];
      data.pt = dataValue[1];
      data.cent = dataValue[2];
      data.nsig = atof(dataValue[4].c_str());
      data.nsigerr = atof(dataValue[5].c_str());
      data.npr = atof(dataValue[8].c_str());
      data.nprerr = atof(dataValue[9].c_str());
      data.nnp = atof(dataValue[10].c_str());
      data.nnperr = atof(dataValue[11].c_str());
      dataValueUseful.push_back(data);
    }
  }
  finput.close();
  
  // Remove duplicate entries (It happens when a bin doesn't have a correct fit result)
  dataValueUseful.unique(CheckSameEntries);

  // Sort the final value array with given order (needs to be corrected!!!)
  dataValueUseful.sort(ComparatorWithArray);

  // If there are missing entries in dataValueUseful, find which bin is missing
  if (FindMissingElement(dataValueUseful)) return -3;

  // Write a txt file with sorted results
  char *outputName;
  if (argc > 2) outputName = argv[2];
  else {
    std::cout << "./a.out [input file] [output file]" << std::endl;
    return -2;
  }
  fstream foutput;
  foutput.open(outputName, ios_base::out|ios_base::trunc);
  if (!foutput.good()) {
    std::cout << "Cannot open output file: " << outputName << std::endl;
    return -1;
  }
  for (it_eachRow = dataValueUseful.begin(); it_eachRow != dataValueUseful.end(); it_eachRow++) {
    foutput << (*it_eachRow).nsig << "\t"
      << (*it_eachRow).nsigerr << "\t"
      << (*it_eachRow).npr << "\t"
      << (*it_eachRow).nprerr << "\t"
      << (*it_eachRow).nnp << "\t"
      << (*it_eachRow).nnperr << std::endl;
    std::cout << std::setiosflags(ios::left) 
      << std::setw(14) << (*it_eachRow).rap << "\t" << std::setw(10) << (*it_eachRow).pt << "\t" << std::setw(7) << (*it_eachRow).cent << "\t"
      << (*it_eachRow).nsig  << "\t"
      << (*it_eachRow).nsigerr << "\t"
      << (*it_eachRow).npr << "\t"
      << (*it_eachRow).nprerr << "\t"
      << (*it_eachRow).nnp << "\t"
      << (*it_eachRow).nnperr << std::endl;
  }
  foutput.close();

  return 0;
}
