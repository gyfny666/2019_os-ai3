//最近最久未使用的页面置换算法 
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
	numberOfcode=rand()%200;//假设有n条指令需要调用
	for(int i=0;i<numberOfcode;i++)
		codeIndex[i]=rand()%320; 
	printf("产生的需要调入的指令的条数为 ：%d\n",numberOfcode);
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
	printf("预调入完成，结果如下 ：\n");
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
	//讲change_one中的东西置换出来
	useFre[change_one]=0;
	int oldPage=codeIndexInMemry[change_one];
	printf("将%d换出，与此同时将%d换出\n",oldPage,page); 
	isInMemry[oldPage]=0;
	isInMemry[page]=1;
	codeIndexInMemry[change_one]=page;//把当前的page放到原本来的地方 
	codeToIndex[page]=change_one;
	codeToIndex[oldPage]=-1; 
}
void LRU()
{
	for(int i=0;i<numberOfcode;i++){
		int page=codeIndex[i]/10;
		printf("需要用到的是第%d行代码，它在%d页\n",codeIndex[i],page);
		if(CheckInMemry(page)){
			//如果已经在虚存中了 
			for(int i=0;i<10;i++)
				useFre[i]++;
			useFre[codeToIndex[page]]=0;
			printf("第%d页已经在虚存中\n",page); 
		}
			else{
				printf("第%d不在虚存中，启用LRU\n");
				change(page);
				printf("置换后在虚存中的情况如下：\n");
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
	//因为需要执行的指令是一次性产生的，所以我们在执行之前已经知道了那些指令在接下来需要呗调入，所以我们提前采用预调入算法
	pre_insert(); 
	lack_page=0;
	LRU();//调用最近最久未使用算法 
	printf("缺页次数为： %d\n",lack_page);
    printf("命中率为：%f\n",1.0-lack_page*1.0/numberOfcode);
	return 0;
}