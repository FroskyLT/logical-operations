#include <iostream>
#include <bitset>
#include <vector>
#include <fstream>

std::vector<int> dec_to_bin(int dec);
void checkOperations(std::vector<int> first, std::vector<int> second);

std::vector<int> XOR1(std::vector<int> A, std::vector<int> B);
std::vector<int> XOR2(std::vector<int> A, std::vector<int> B);
std::vector<int> XOR3(std::vector<int> A, std::vector<int> B);
std::vector<int> XOR4(std::vector<int> A, std::vector<int> B);


const int bitsetSize = 8;

int main(int argc, char* argv[])
{

	if (argc == 1) { std::cout << "No arguments"; return 0; }

	int Adec, Bdec;
	Adec = strtol(argv[1], nullptr, 10);
	Bdec = strtol(argv[2], nullptr, 10);

	std::vector<int> A = dec_to_bin(Adec), B = dec_to_bin(Bdec);

	// checkOperations(A, B);

	std::vector<int>
		A_xor1_B = XOR1(A, B),
		A_xor2_B = XOR2(A, B),
		A_xor3_B = XOR3(A, B),
		A_xor4_B = XOR4(A, B);

	std::string xor1_logical_seq = " (~A · B) + (A · ~B) ,";
	std::string xor2_logical_seq = " (~(~(A · ~(A · B)) · (~(~(A · B) · B))) ,";
	std::string xor3_logical_seq = " ((A + B) · ~(A · B)) ,";
	std::string xor4_logical_seq = " ((~A + ~B) · (A + B)) \n";

	std::ofstream fr("output.csv");

	fr << "Name, Surname, /\n";
	fr << Adec << "," << Bdec << "\n";
	fr << xor1_logical_seq << xor2_logical_seq;
	fr << xor3_logical_seq << xor4_logical_seq;
	for (auto it : A_xor1_B) fr << it; fr << ",";
	for (auto it : A_xor2_B) fr << it; fr << ",";
	for (auto it : A_xor3_B) fr << it; fr << ",";
	for (auto it : A_xor4_B) fr << it;

	fr.close();

	std::cout << "Check you output.csv";

	return 0;
}

std::vector<int> dec_to_bin(int dec) {
	std::string bin = std::bitset<bitsetSize>(dec).to_string();

	std::vector<int> intBin;

	for (auto it : bin) intBin.push_back(it - '0');

	//std::cout << dec << " " << bin << std::endl;

	return intBin;
}

void checkOperations(std::vector<int> first, std::vector<int> second) {
	for (auto it : first) std::cout << it;
	std::cout << "\n";
	for (auto it : second) std::cout << it;

	std::cout << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < bitsetSize; i++)
		std::cout << (first[i] && second[i]); std::cout << " AND " << std::endl;
	for (int i = 0; i < bitsetSize; i++)
		std::cout << (first[i] || second[i]); std::cout << " OR " << std::endl;
	for (int i = 0; i < bitsetSize; i++)
		std::cout << !(first[i] && second[i]); std::cout << " XAND " << std::endl;

	//std::cout <<  !(0)   << std::endl;		NOT
	//std::cout <<  (0&&0) << std::endl;		AND
	//std::cout <<  (0||0) << std::endl;		OR
	//std::cout << !(0&&0) << std::endl;		XAND
	//std::cout << !(0||0) << std::endl;		XOR
}


std::vector<int> XOR1(std::vector<int> A, std::vector<int> B) {

	std::vector<int> notA_and_B, A_and_notB, A_or_B, result;
	std::cout << "\n";

	for (int i = 0; i < bitsetSize; i++) notA_and_B	.push_back(!A[i] && B[i]);
	for (int i = 0; i < bitsetSize; i++) A_and_notB	.push_back(A[i] && !B[i]);
	for (int i = 0; i < bitsetSize; i++) result		.push_back(notA_and_B[i] || A_and_notB[i]);


	return result;
}

std::vector<int> XOR2(std::vector<int> A, std::vector<int> B) {

	std::vector<int> A_nand_B, A_nand_AnandB, AnandB_nand_B, result;

	for (int i = 0; i < bitsetSize; i++) A_nand_B		.push_back(!(A[i] && B[i]));
	for (int i = 0; i < bitsetSize; i++) A_nand_AnandB	.push_back(!(A[i] && A_nand_B[i]));
	for (int i = 0; i < bitsetSize; i++) AnandB_nand_B	.push_back(!(A_nand_B[i] && B[i]));
	for (int i = 0; i < bitsetSize; i++) result			.push_back(!(AnandB_nand_B[i] && A_nand_AnandB[i]));


	return result;
}

std::vector<int> XOR3(std::vector<int> A, std::vector<int> B) {
	
	std::vector<int> A_or_B, A_and_B, notAandB, result;

	for (int i = 0; i < bitsetSize; i++) A_or_B		.push_back(A[i] || B[i]);
	for (int i = 0; i < bitsetSize; i++) A_and_B	.push_back(A[i] && B[i]);
	for (int i = 0; i < bitsetSize; i++) notAandB	.push_back(!A_and_B[i]);
	for (int i = 0; i < bitsetSize; i++) result		.push_back(A_or_B[i] && notAandB[i]);

	return result;
}

std::vector<int> XOR4(std::vector<int> A, std::vector<int> B) {

	std::vector<int> A_or_B, notA_or_notB, result;

	for (int i = 0; i < bitsetSize; i++) A_or_B			.push_back(A[i] || B[i]);
	for (int i = 0; i < bitsetSize; i++) notA_or_notB	.push_back(!A[i] || !B[i]);
	for (int i = 0; i < bitsetSize; i++) result			.push_back(A_or_B[i] && notA_or_notB[i]);

	return result;
}