// TestCrypto.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../../CommonLib.h"
#include "../../crypto/winapi/CryptoFactory.h"
#include "../../str/str.h"


void TestXTS();

int main()
{ 
	try
	{

		TestXTS();

		return 0;

		CommonLib::crypto::IRandomGeneratorPtr ptrRandomGenerator = CommonLib::crypto::winapi::CCryptoFactory::CreateRandomGenerator();
		CommonLib::crypto::IKeyGeneratorPtr ptrKeyGenerator = CommonLib::crypto::winapi::CCryptoFactory::CreateKeyGenerator();
		CommonLib::crypto::IAESCipherPtr ptrAesCipher= CommonLib::crypto::winapi::CCryptoFactory::CreateAESCipher(CommonLib::crypto::AES_256, false, CommonLib::crypto::CipherChainMode::ECB);
		CommonLib::crypto::IAESCipherPtr ptrAesCipherWithPadding = CommonLib::crypto::winapi::CCryptoFactory::CreateAESCipher(CommonLib::crypto::AES_256, true, CommonLib::crypto::CipherChainMode::ECB);
	
		uint32_t blockSize = ptrAesCipher->GetBlockSize();
		uint32_t keySize = ptrAesCipher->GetKeySize();

		CommonLib::crypto::crypto_astr pwd = "123456789";
		CommonLib::crypto::crypto_vector pwdSalt(64, 0);
		CommonLib::crypto::crypto_vector keyData;

		ptrRandomGenerator->GenRandom(pwdSalt);

		ptrRandomGenerator->GenRandom(ptrAesCipher->GetIVData(), ptrAesCipher->GetIVSize());
		

		ptrKeyGenerator->DeriveKeyPBKDF2(pwd, pwdSalt,  2048, keyData, keySize);

 
		ptrAesCipher->SetKey(keyData);

		astr plainText;
		plainText.resize(16, 'a');

		int32_t size =  ptrAesCipher->GetBufferSize(plainText.length());
		std::vector<byte_t> butChiperText(size, 0);
		ptrAesCipher->Encrypt((const byte*)plainText.c_str(), plainText.size(), (byte*)plainText.data(), plainText.size());

		int32_t size1 = ptrAesCipher->GetBufferSize(butChiperText.size());
		std::vector<byte> plainText1;
		plainText1.resize(size1);
		ptrAesCipher->Decrypt((const byte*)plainText.data(), plainText.size(), (byte*)plainText.data(), plainText.size());
	
	}
	catch (std::exception& exc)
	{
		std::cout << "Error: " << exc.what();
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
