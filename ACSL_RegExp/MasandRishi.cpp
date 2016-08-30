#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {

	string allInputStrings[10];

	string originalInputString;

	getline(cin, originalInputString);

	stringstream inputStream(originalInputString);
	string s;

	int curInd = 0;

	while (inputStream >> s) {
		int pos = s.find(", ");
		if (pos >= 0) {
			s.erase(pos, pos);
		}
		allInputStrings[curInd] = s;
		curInd++;
		
		if (inputStream.peek() == ',' || inputStream.peek() == ' ') {
			inputStream.ignore();
		}
	}

	for (int i = 0; i < 9; i++) {
		if (allInputStrings[i].find(",") != string::npos) {
			allInputStrings[i].erase(allInputStrings[i].find(","), allInputStrings[i].find(","));
		}
	}

	for (int i = 0; i < 10; i++) {
		//cout << allInputStrings[i] << endl;
	}

	for (int i = 0; i < 5; i++) {
		string regExString;
		getline(cin, regExString);

		if (regExString.find(".") != string::npos) {
			int foundCount = 0;
			for (int j = 0; j < 10; j++) {
				string beforeDot = regExString.substr(0, regExString.find("."));
				string afterDot = regExString.substr(regExString.find(".") + 1);
				if (allInputStrings[j].find(beforeDot) != string::npos && allInputStrings[j].find(afterDot) != string::npos) {
					char temp = (allInputStrings[j])[(allInputStrings[j].find(beforeDot) + beforeDot.length())];
					(allInputStrings[j])[(allInputStrings[j].find(beforeDot) + beforeDot.length())] = '.';
					if ((allInputStrings[j].find(beforeDot) + beforeDot.length() + 1) == allInputStrings[j].find(afterDot) && regExString.length() == allInputStrings[j].length()) {
						if (foundCount == 0) {
							(allInputStrings[j])[(allInputStrings[j].find(beforeDot) + beforeDot.length())] = temp;
							cout << allInputStrings[j];
							foundCount++;
						}
						else {
							(allInputStrings[j])[(allInputStrings[j].find(beforeDot) + beforeDot.length())] = temp;
							cout << ", " << allInputStrings[j];
							foundCount++;
						}
					}
					else {
						(allInputStrings[j])[(allInputStrings[j].find(beforeDot) + beforeDot.length())] = temp;
					}
				}
			}
			cout << endl;
		}
		else if (regExString.find("[^") != string::npos) {
			int foundCount = 0;
			int strLength = regExString.find("[^") + (regExString.length() - regExString.find("]") - 1) + 1;
			string notPossibleChars = regExString.substr(regExString.find("[^") + 2, regExString.find("]") - regExString.find("[^") - 2);
			for (int j = 0; j < 10; j++) {
				if (allInputStrings[j].length() == strLength) {
					int notEqualToAny = 0;
					for (int y = 0; y < notPossibleChars.length(); y++) {
						if ((allInputStrings[j])[regExString.find("[^")] != notPossibleChars[y]) {
							notEqualToAny++;
							if (notEqualToAny == notPossibleChars.length()) {
								if (foundCount == 0) {
									cout << allInputStrings[j];
									foundCount++;
								}
								else {
									cout << ", " << allInputStrings[j];
									foundCount++;
								}
							}
						}
					}
				}
			}
			cout << endl;
		}
		else if (regExString.find("[") != string::npos){
			int foundCount = 0;
			int strLength = regExString.find("[") + (regExString.length() - regExString.find("]") - 1) + 1;
			string possibleChars = regExString.substr(regExString.find("[") + 1, regExString.find("]") - regExString.find("[") - 1);
			for (int j = 0; j < 10; j++) {
				if (allInputStrings[j].length() == strLength) {
					for (int y = 0; y < possibleChars.length(); y++) {
						if ((allInputStrings[j])[regExString.find("[")] == possibleChars[y]) {
							if (foundCount == 0) {
								cout << allInputStrings[j];
								foundCount++;
							}
							else {
								cout << ", " << allInputStrings[j];
								foundCount++;
							}
						}
					}
				}
			}
			cout << endl;
		}
		else if (regExString.find("*") != string::npos) {
			//cout << endl;
			//for (int a = 0; a < 10; a++) {
			//	cout << allInputStrings[a] << ", ";
			//}
			//cout << endl;
			int foundCount = 0;
			string beforeStar = "";
			string afterStar = regExString.substr(regExString.find("*") + 1);
			if (regExString.find("*") != 1) {
				beforeStar = regExString.substr(0, regExString.find("*") - 1);
			}
			for (int j = 0; j < 10; j++) {
				if (allInputStrings[j].find(beforeStar) != string::npos) {
					if (allInputStrings[j].find(beforeStar) == 0) {
						if (afterStar == allInputStrings[j].substr(allInputStrings[j].length() - afterStar.length())) {
							string inBetween = allInputStrings[j].substr(beforeStar.length(), allInputStrings[j].find(afterStar) - beforeStar.length());
							if (inBetween.length() > 0) {
								bool allMatches = true;
								//cout << inBetween << endl;
								for (int p = 0; p < inBetween.length(); p++) {
									if (inBetween[p] == regExString[regExString.find("*") - 1]) {
										
									}
									else {
										allMatches = false;
									}
								}
								if (allMatches) {
									if (foundCount == 0) {
										cout << allInputStrings[j];
										foundCount++;
									}
									else {
										cout << ", " << allInputStrings[j];
										foundCount++;
									}
								}
							}
							else {
								if (regExString.length() - 2 == allInputStrings[j].length()) {
									if (foundCount == 0) {
										cout << allInputStrings[j];
										foundCount++;
									}
									else {
										cout << ", " << allInputStrings[j];
										foundCount++;
									}
								}
							}
						}
					}
				}
			}
			cout << endl;
		}
		else if (regExString.find("{") != string::npos) {
			int foundCount = 0;
			string beforeStar = "";
			string afterStar = regExString.substr(regExString.find("}") + 1);
			if (regExString.find("{") != 1) {
				beforeStar = regExString.substr(0, regExString.find("{") - 1);
			}
			int min = regExString[regExString.find("{") + 1] - '0';
			int max = regExString[regExString.find("}") - 1] - '0';
			for (int j = 0; j < 10; j++) {
				if (allInputStrings[j].find(beforeStar) != string::npos) {
					if (allInputStrings[j].find(beforeStar) == 0) {
						if (afterStar == allInputStrings[j].substr(allInputStrings[j].length() - afterStar.length())) {
							string inBetween = allInputStrings[j].substr(beforeStar.length(), allInputStrings[j].find(afterStar) - beforeStar.length());
							//cout << "IB: " << inBetween << " l: " << allInputStrings[j].find(afterStar) - beforeStar.length() << endl;
							//cout << "min: " << min << " max: " << max << " IB: " << inBetween.length() << endl;
							if (inBetween.length() >= min && inBetween.length() <= max) {
								//cout << "IB: " << inBetween << endl;
								//cout << regExString[regExString.find("{") - 1] << endl;
								bool allMatches = true;
								for (int p = 0; p < inBetween.length(); p++) {
									if (inBetween[p] == regExString[regExString.find("{") - 1]) {

									}
									else {
										allMatches = false;
									}
								}
								if (allMatches) {
									if (foundCount == 0) {
										cout << allInputStrings[j];
										foundCount++;
									}
									else {
										cout << ", " << allInputStrings[j];
										foundCount++;
									}
								}
							}
						}
					}
				}
			}
			cout << endl;
		}
	}

	return 0;

}