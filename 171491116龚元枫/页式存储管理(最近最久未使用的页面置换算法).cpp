//������δʹ�õ�ҳ���û��㷨 
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<ctime>
#include<cstdlib>
using namespace std;
const int max_page=10; 
const int max_number_code=1000+5; 
int codeIndexInMemry[max_page];
int codeToIndex[32];
int codeIndex[max_number_code];
int numberOfcode;
bool isInMemry[32];
int useFre[10];
int lack_page;
void Pro_page()
{
	srand(time(0));
	numberOfcode=rand()%200;//������n��ָ����Ҫ����
	for(int i=0;i<numberOfcode;i++)
		codeIndex[i]=rand()%320; 
	printf("��������Ҫ�����ָ�������Ϊ ��%d\n",numberOfcode);
	for(int i=0;i<numberOfcode;i++){
		printf("%-5d",codeIndex[i]);
		if(i%10==9)
			printf("\n");
	} 
	printf("\n");
}
void pre_insert()
{
	int usedPageNumber=0;
	int page;
	for(int i=0;i<32;i++)
		codeToIndex[i]=-1;
	for(int i=0;i<numberOfcode	;i++){
		page=codeIndex[i]/10;
		if(!isInMemry[page]){
			codeIndexInMemry[usedPageNumber]=page;
			codeToIndex[page]=usedPageNumber;
			isInMemry[page]=1;
			usedPageNumber++;			
		}
		if(usedPageNumber>=10)
			break;
	}
	printf("Ԥ������ɣ�������� ��\n");
	for(int i=0;i<10;i++){
		printf("%d ",codeIndexInMemry[i]);
	}
	printf("\n");
}
bool CheckInMemry(int page)
{
	return isInMemry[page]; 
}
void change(int page)
{
	int change_one=0;
	for(int i=1;i<10;i++)
		if(useFre[change_one]<useFre[i])
			change_one=i;
	//��change_one�еĶ����û�����
	useFre[change_one]=0;
	int oldPage=codeIndexInMemry[change_one];
	printf("��%d���������ͬʱ��%d����\n",oldPage,page); 
	isInMemry[oldPage]=0;
	isInMemry[page]=1;
	codeIndexInMemry[change_one]=page;//�ѵ�ǰ��page�ŵ�ԭ�����ĵط� 
	codeToIndex[page]=change_one;
	codeToIndex[oldPage]=-1; 
}
void LRU()
{
	for(int i=0;i<numberOfcode;i++){
		int page=codeIndex[i]/10;
		printf("��Ҫ�õ����ǵ�%d�д��룬����%dҳ\n",codeIndex[i],page);
		if(CheckInMemry(page)){
			//����Ѿ���������� 
			for(int i=0;i<10;i++)
				useFre[i]++;
			useFre[codeToIndex[page]]=0;
			printf("��%dҳ�Ѿ��������\n",page); 
		}
			else{
				printf("��%d��������У�����LRU\n");
				change(page);
				printf("�û���������е�������£�\n");
				for(int i=0;i<10;i++)
					printf("%d ",codeIndexInMemry[i]);
				printf("\n");
				lack_page++;				
			}
	} 
} 
int main()
{
	Pro_page();
	//��Ϊ��Ҫִ�е�ָ����һ���Բ����ģ�����������ִ��֮ǰ�Ѿ�֪������Щָ���ڽ�������Ҫ�µ��룬����������ǰ����Ԥ�����㷨
	pre_insert(); 
	lack_page=0;
	LRU();//����������δʹ���㷨 
	printf("ȱҳ����Ϊ�� %d\n",lack_page);
    printf("������Ϊ��%f\n",1.0-lack_page*1.0/numberOfcode);
	return 0;
}