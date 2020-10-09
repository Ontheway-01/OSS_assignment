//2020-10-08 programming - practice 05
//text에서 target 단어들을 replce 단어로 변경 후 전광판처럼 스크롤하여 출력하는 프로그램
//소프트웨어학부 1학년 이은화(20201945)

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

//멈추는 시간 설정
#define milliseconds 60

//한번 밀리기
void spin(char* str, int nStrLength) {
	char pszTemp = 0;
	pszTemp = str[0];
	for (int i = 0;i<nStrLength-1; i++) {
		str[i] = str[i + 1];
	}

	str[nStrLength - 1] = pszTemp;
}

//한바퀴 돌기
void oneWholeTurn(char* str) {
	int length = strlen(str);
	for (int i = 0; i < length; i++) {
		printf(str);
		system("cls");
		Sleep(milliseconds);
		spin(str, length);
	}
}

//n바퀴 돌기
void scroll(char* str, int n) {
	for (int i = 0; i < n; i++) {
		oneWholeTurn(str);
	}
	printf(str);
	system("cls");
	Sleep(milliseconds);
}

//target 글자수가 replace 글자수보다 작은 경우 (원래의 문자열 길이 유지하므로 뒷부분은 날라감)
void strPushRight(char* str, int n) {
	int nStr = strlen(str);
	int iCurStr = strlen(str) - 1 - n;
	for (int i = iCurStr; i >= 0; i--) {
		str[i + n] = str[i];
	}

}

//target 글자수가 replace 글자수보다 큰 경우 (원래의 문자열 길이 유지하므로 글자수 차이만큼 빈칸 생성)
void strPushLeft(char* str, int n) {
	int nStr = strlen(str);
	int iCurStr = strlen(str) - 1 - n;
	char Space = ' ';
	
	for (int i = 0; i <= iCurStr; i++) {
		str[i] = str[i + n];
	}

	for (int i = nStr - n; i < nStr; i++) {
		str[i] = Space;
	}
}

//target을 replace로 변경 다만, 문자열 길이는 유지
char* replaceText(char* text, char* target, char* replace, int maxStr) {
	char* pChangePoint = text;
	int nDiffereence = 0;
	
	while (1) {
		pChangePoint = strstr(pChangePoint, target);
		
		if (pChangePoint == NULL)
			break;
		
		if (strlen(target) > strlen(replace)) {
			nDiffereence = strlen(target) - strlen(replace);
			strPushLeft(pChangePoint, nDiffereence);
		}

		else if (strlen(target) < strlen(replace)) {
			nDiffereence = strlen(replace) - strlen(target);
			strPushRight(pChangePoint, nDiffereence);
		}
		
		for (int i = 0; i < strlen(replace); i++) {
			*(pChangePoint + i) = *(replace + i);
		}
		pChangePoint = pChangePoint + strlen(replace);
	}

	return  text;
}

int main() {
	char text[512] = { 0 };
	char target[512]  = { 0 };
	char replace[512] = { 0 };
	int maxStr = 0;
	int nTimes = 0;

	printf("Enter a text:");
	scanf("%[^\n]", text);

	printf("Enter a word to find:");
	scanf(" %[^\n]", target);
	
	printf("Enter a a new word:");
	scanf(" %[^\n]", replace);

	maxStr = strlen(text) + 1;
	
	char *retText = replaceText(text, target, replace, maxStr);

	printf("Enter the number of times you want to scroll:");
	scanf("%d", &nTimes);

	system("cls");
	Sleep(milliseconds);

	

	scroll(text, nTimes);



	return 0;

}