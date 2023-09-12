#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct WORD
{ 
	char Name[256]; 
	char Meaning[512]; 
};


void nhap(struct WORD w[], int n){
	for(int i = 0; i < n; i++){
		printf("Nhap thong tin mot tu\n");
		printf("Nhap Name: ");
		gets(w[i].Name);
		printf("Nhap Meaning: ");
		gets(w[i].Meaning);
	}
}

void display(struct WORD w[], int n){
	printf("Xuat thong tin cac tu\n");
	for(int i = 0; i < n; i++){
		printf("Name: %s\n",w[i].Name);
		printf("Nhap Meaning: %s\n",w[i].Meaning);
	}
	
}

void sapxepname(struct WORD w[], int n){
	WORD tmp;
	for(int i = 0; i < n - 1; i++){
		for(int j = i + 1; j < n; j++){
			if(strcmp(w[i].Name,w[j].Name) > 0){
				tmp = w[i];
				w[i] = w[j];
				w[j] = tmp;
			}
		}
	}
}

int timkiemname_binarysearch(struct WORD w[], int l, int r, char target[]){
	while(l <= r){
		int mid = (l + r) / 2;
		int check = strcmp(w[mid].Name, target);
		if(check == 0) return mid;
		if(check < 0) l = mid + 1;
		else r = mid - 1;
	}
	return -1;
}

void ghimottu(){
	struct WORD w;
	FILE* file = fopen("word.bin", "ab");
	if (file == NULL)
    {
        return;
    }
	printf("Nhap thong tin mot tu de ghi vao tep\n");
	printf("Nhap Name: ");
	gets(w.Name);
	printf("Nhap Meaning: ");
	gets(w.Meaning);
	fwrite(&w, sizeof(w), 1, file);

	fclose(file);
}

void doctep(){
    struct WORD w;
    FILE *file = fopen("word.bin", "rb"); 

    if (file == NULL){
        return;
    }

    printf("\nDanh sach cac tu trong tep:\n");
    while (fread(&w, sizeof(struct WORD), 1, file) == 1){
        printf("Name: %s\n",w.Name);
		printf("Meaning: %s\n",w.Meaning);
    }

    fclose(file);
}

void ghimotmangvaofile(int a[], int &n){
	FILE *file = fopen("mang.txt","w");
	if (file == NULL){
        return;
    }
    printf("Nhap vao so luong phan tu muon nhap vao mang: ");
	scanf("%d",&n);
	for(int i = 0; i < n; i++){
		printf("nhap vao phan tu thu %d: ", i + 1);
		scanf("%d",&a[i]);
	}
	fwrite(a,sizeof(int),n,file);
	fclose(file);
}

void docmotmangtufile(int a[], int n){
	FILE *file = fopen("mang.txt","r");
	if (file == NULL){
        return;
    }
//	n = sizeof(a) / sizeof(a[0]);
	printf("mang trong da co trong file\n");	
	for (int i = 0; i < n; i++) {
        if (fread(&a[i], sizeof(int), 1, file) != 1) {
            break; 
        }
        printf("Phan tu thu %d: %d\n", i + 1, a[i]);
    }
	fclose(file);
}

void capnhatmeaning(struct WORD w[], int n, char target[], char newmeaning[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(w[i].Name, target) == 0) {
            strcpy(w[i].Meaning, newmeaning);
            break;
        }
	}
}

void capnhatmeaningtrongtep(char target[], char newmeaning[]) {
    struct WORD w;
	FILE *file = fopen("word.bin", "rb+");
    if (file == NULL) {
        return;
    }
	int check = 0;
    while (fread(&w, sizeof(struct WORD), 1, file) == 1) {
        if (strcmp(w.Name, target) == 0) {
            check = 1;
			fseek(file, -(int)sizeof(struct WORD), SEEK_CUR);
            strcpy(w.Meaning, newmeaning);;
            fwrite(&w, sizeof(struct WORD), 1, file); 
            break;
        }
    }
	if(!check){
		printf("Tu ban muon doi khong co trong tu dien ^__^\n");
	}
    fclose(file);
}

void xoatutrongtep(char tucanxoa[]) {
    FILE *file = fopen("word.bin", "rb");
    if (file == NULL) {
        return;
    }

    FILE *tempfile = fopen("temp_word.bin", "wb");
    if (tempfile == NULL) {
        fclose(file);
        return;
    }

    struct WORD w;
    int found = 0;
    while (fread(&w, sizeof(struct WORD), 1, file) == 1) {
        if (strcmp(w.Name, tucanxoa) == 0) {
            //Neu tim thay thi bo qua khong ghi lai
			found = 1;
        } else {
            fwrite(&w, sizeof(struct WORD), 1, tempfile); 
        }
    }

    fclose(file);
    fclose(tempfile);
    
	remove("word.bin");
    rename("temp_word.bin", "word.bin");

    if (!found) {
        printf("Tu ban muon xoa trong tep không c0 ^___^\n");
    }
}

    
int main(){
	struct WORD w[1000];
	char target[500];
	int choice, n, k, a[100];
	do{
		printf("\t\tMenu Function\n");
		printf("|---------------------------------------------|\n");
		printf("1. Nhap thong tin mot tu\n");
		printf("2. Xuat thong tin cac tu trong tu dien\n");
		printf("3. Sap xep theo name tang dan\n");
		printf("4. tim kiem tu theo name\n");
		printf("5. Ghi mot tu vao tep\n");
		printf("6. Ghi mot mang len File\n");
		printf("7. Doc cac tu trong tep\n");
		printf("8. Doc mang trong tep\n");
		printf("9. Cap nhap Meaning cua mot Word trong tep\n");
		printf("10. Xoa mot tu khoi tep\n");
		printf("|----------------------------------------------|\n");
		printf("Muon Thoat Khoi Menu hay chon so 0\n");
		printf("Nhap vao chuc nang ban muon su dung: ");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				printf("Nhap vao so luong tu muon nhap: ");
				scanf("%d",&n);
				getchar();
				nhap(w,n);
				break;
			case 2:
				display(w,n);
				break;
			case 3:
				sapxepname(w,n);
				break;
			case 4:
				{
				getchar();
				printf("Nhap vao tu can tim: ");
				gets(target);
				int result = timkiemname_binarysearch(w,0,n,target);
				if(result != -1){
					printf("Name: %s\n",w[result].Name);
					printf("Meaning: %s\n",w[result].Meaning);
				}else{
					printf("NOT FOUND NAME ^-^");
				}
				break;
				}
			case 5:
				getchar();
				ghimottu();
				break;
			case 7:
				doctep();
				break;
			case 6:
				ghimotmangvaofile(a, k);
				break;
			case 8:
				docmotmangtufile(a, k);
				break;
			case 9:
				getchar();
				char tumuondoi[50], nghiamoi[50];
				printf("Nhap vao tu muon cap nhat nghia trong file: ");
				gets(tumuondoi);
				printf("Nhap vao nghia muon cap nhat: ");
				gets(nghiamoi);
				capnhatmeaningtrongtep(tumuondoi, nghiamoi);
				break;
			case 10:
				getchar();
				char tumuonxoa[50];
				gets(tumuonxoa);
				xoatutrongtep(tumuonxoa);
				break;
		}
	}while((choice > 0) && (choice < 11));
	return 0;
}





	
