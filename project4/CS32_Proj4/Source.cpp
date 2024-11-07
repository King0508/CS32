#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>
using namespace std;
void createRevision(std::istream& fold, std::istream& fnew, std::ostream& frevision);
bool revise(std::istream& fold, std::istream& frevision, std::ostream& fnew);

bool runtest(string oldName, string newName, string revisionName, string newName2)
{
	if (revisionName == oldName || revisionName == newName ||
		newName2 == oldName || newName2 == revisionName ||
		newName2 == newName)
	{
		cerr << "Files used for output must have names distinct from other files" << endl;
		return false;
	}
	ifstream oldFile(oldName);
	if (!oldFile)
	{
		cerr << "Cannot open " << oldName << endl;
		return false;
	}
	ifstream newFile(newName);
	if (!newFile)
	{
		cerr << "Cannot open " << newName << endl;
		return false;
	}
	ofstream revisionFile(revisionName);
	if (!revisionFile)
	{
		cerr << "Cannot create " << revisionName << endl;
		return false;
	}
	createRevision(oldFile, newFile, revisionFile);
	revisionFile.close();

	oldFile.clear();   // clear the end of file condition
	oldFile.seekg(0);  // reset back to beginning of the file
	ifstream revisionFile2(revisionName);
	if (!revisionFile2)
	{
		cerr << "Cannot read the " << revisionName << " that was just created!" << endl;
		return false;
	}
	ofstream newFile2(newName2);
	if (!newFile2)
	{
		cerr << "Cannot create " << newName2 << endl;
		return false;
	}
	assert(revise(oldFile, revisionFile2, newFile2));
	newFile2.close();

	newFile.clear();
	newFile.seekg(0);
	ifstream newFile3(newName2);
	if (!newFile)
	{
		cerr << "Cannot open " << newName2 << endl;
		return false;
	}
	if (!equal(istreambuf_iterator<char>(newFile), istreambuf_iterator<char>(),
		istreambuf_iterator<char>(newFile3), istreambuf_iterator<char>()))
	{
		cerr << newName2 << " is not identical to " << newName
			<< "; test FAILED" << endl;
		return false;
	}
	return true;
}

int main()
{

	ifstream greeneggs1("C:/Users/kings/OneDrive/Desktop/CS32/CS32_Proj4/CS32_Proj4/p4testwindows/greeneggs1.txt", ios::binary);
	ifstream greeneggs2("C:/Users/kings/OneDrive/Desktop/CS32/CS32_Proj4/CS32_Proj4/p4testwindows/greeneggs2.txt", ios::binary);
	ofstream greeneggs("greeneggs.txt", ios::binary);
	createRevision(greeneggs1, greeneggs2, greeneggs); 

	ifstream mallmart1("C:/Users/kings/OneDrive/Desktop/CS32/CS32_Proj4/CS32_Proj4/p4testwindows/mallmart1.txt", ios::binary);
	ifstream mallmart2("C:/Users/kings/OneDrive/Desktop/CS32/CS32_Proj4/CS32_Proj4/p4testwindows/mallmart2.txt", ios::binary);
	ofstream mallmart("mallmart.txt", ios::binary);
	createRevision(mallmart1, mallmart2, mallmart); 

	ifstream warandpeace1("C:/Users/kings/OneDrive/Desktop/CS32/CS32_Proj4/CS32_Proj4/p4testwindows/warandpeace1.txt", ios::binary);
	ifstream warandpeace2("C:/Users/kings/OneDrive/Desktop/CS32/CS32_Proj4/CS32_Proj4/p4testwindows/warandpeace2.txt", ios::binary);
	ofstream warandpeace("warandpeace.txt", ios::binary);
	createRevision(warandpeace1, warandpeace2, warandpeace); 

	ifstream strange1("C:/Users/kings/OneDrive/Desktop/CS32/CS32_Proj4/CS32_Proj4/p4testwindows/strange1.txt", ios::binary);
	ifstream strange2("C:/Users/kings/OneDrive/Desktop/CS32/CS32_Proj4/CS32_Proj4/p4testwindows/strange2.txt", ios::binary);
	ofstream strange("strange.txt", ios::binary);
	createRevision(strange1, strange2, strange);

	ifstream cr1("C:/Users/kings/Downloads/crazyrandom1k2.txt", ios::binary);
	ifstream cr2("C:/Users/kings/Downloads/crazyrandom1k1.txt", ios::binary);
	ofstream cr("cr.txt", ios::binary);
	createRevision(cr1, cr2, cr);

	std::cerr << "pass";
	assert(runtest("C:/Users/kings/OneDrive/Desktop/CS32/CS32_Proj4/CS32_Proj4/p4testwindows/mallmart1.txt",
		"C:/Users/kings/OneDrive/Desktop/CS32/CS32_Proj4/CS32_Proj4/p4testwindows/mallmart2.txt", "mallmart.txt", "m.txt"));
	assert(runtest("C:/Users/kings/OneDrive/Desktop/CS32/CS32_Proj4/CS32_Proj4/p4testwindows/greeneggs1.txt",
		"C:/Users/kings/OneDrive/Desktop/CS32/CS32_Proj4/CS32_Proj4/p4testwindows/greeneggs2.txt", "greeneggs.txt", "g.txt"));
	assert(runtest("C:/Users/kings/OneDrive/Desktop/CS32/CS32_Proj4/CS32_Proj4/p4testwindows/warandpeace1.txt",
		"C:/Users/kings/OneDrive/Desktop/CS32/CS32_Proj4/CS32_Proj4/p4testwindows/warandpeace2.txt", "warandpeace.txt", "w.txt"));
	assert(runtest("C:/Users/kings/OneDrive/Desktop/CS32/CS32_Proj4/CS32_Proj4/p4testwindows/strange1.txt",
		"C:/Users/kings/OneDrive/Desktop/CS32/CS32_Proj4/CS32_Proj4/p4testwindows/strange2.txt", "strange.txt", "s.txt"));
	cerr << "Test PASSED" << endl;
}


//#include <iostream>
//#include <sstream>  // for istringstream and ostringstream
//#include <string>
//#include <cassert>
//using namespace std;
//void createRevision(std::istream& fold, std::istream& fnew, std::ostream& frevision);
//bool revise(std::istream& fold, std::istream& frevision, std::ostream& fnew);
//void runtest(string oldtext, string newtext)
//{
//	istringstream oldFile(oldtext);
//	istringstream newFile(newtext);
//	ostringstream revisionFile;
//	createRevision(oldFile, newFile, revisionFile);
//	string result = revisionFile.str();
//	cout << "The revision file length is " << result.size()
//		<< " and its text is " << endl;
//	cout << result << endl;
//
//	oldFile.clear();   // clear the end of file condition
//	oldFile.seekg(0);  // reset back to beginning of the stream
//	istringstream revisionFile2(result);
//	ostringstream newFile2;
//	assert(revise(oldFile, revisionFile2, newFile2));
//	assert(newtext == newFile2.str());
//}
//
//int main()
//{
//	runtest("There's a bathroom on the right.",
//		"There's a bad moon on the rise.");
//	runtest("ABCDEFGHIJBLAHPQRSTUVPQRSTUV",
//		"XYABCDEFGHIJBLETCHPQRSTUVPQRSTQQ/OK");
//	cout << "All tests passed" << endl;
//}