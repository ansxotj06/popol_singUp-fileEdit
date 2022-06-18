//관리자 파일: /Users/moontaeseo/Desktop/codeing/single/project/C/project(FileEdit)_01_c/manager_file
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>  //windows.h 맥버전 - (sleep, cls)


void print_menu(void);  //print_menu 함수원형
int choice_menu(void);  //choice_menu 함수원형
int loginp(void);  //login 함수원형
int fine_data(void);  //회원정보 찾기 함수원형
void SignUp(void);  //임시 회원가입 함수원형
void login_delay(void);  //로그인 지연 함수원형

int main2(void);  //메인2 함수원형 - 파일입출력 함수
void file_loading(void);  //파일 불러오기 함수원형
void file_save(void);  //파일 저장 함수원형
int menu(void);  //메뉴  함수원형
void print_list(void);  //리스트 출력 함수원형
int file_choice(char purpose[10]);  //파일 선택 함수원형
void file_read(int);   //파일 읽기 함수원형
void file_edit(int choice);  //파일 수정 함수원형
void file_delete(int);  //파일 삭제 함수원형
void file_create(void);  //파일 생성 함수원형
void End(void);  //프로그램 종료 함수원형


#define success 1
#define fail 0


struct login_data {  //회원정보 구조체 선언
    char ID[13], PW[13], Name[100], Email[40];
    int Age, CallNumber;
};

struct file_data  //파일데이터 구조체선언
{
    char file_name[1000];  //파일이름 - 경로
};

struct login_data p[5];

struct file_data file[100];  //전역 구조체변수
struct file_data add;  //전역 구조체변수 - (추가 파일)


int count_login = 0;  //전역변수 - (로그인 시도횟수)
int count_member = 1;  //전역변수 - (회원수)

int count_file = 0;  //전역변수 - (파일개수)
int delete = -100;  //전역변수 - (삭제파일)
int addition = 0;  //전역변수 - (추가파일)




int main(void)  //메인함수 - 로그인 프로그램
{

    int choice;  //메뉴선택

    strcpy(p[0].ID, "moontaeseo");
    strcpy(p[0].PW, "moontaeseo");
    strcpy(p[0].Name, "문태서");
    strcpy(p[0].Email, "22sunrin073");
    p[0].Age = 17;
    p[0].CallNumber = 33181668;


    while (1)
    {
        if (count_login > 5)  //로그인 시도횟수가 5초과일 경우
        {
            login_delay();  //로그인 지연 함수실행
        }

        print_menu();  //메뉴출력 함수실행
        choice = choice_menu();  //메뉴선택 함수실행 - 입력값 반환


        switch (choice)
        {
            case 1:  //메뉴 = 1. 로그인

                if (loginp())  //로그인 함수실행 - (반환값)로그인 성공
                {
                    main2();  //페이지 함수실행
                }
                else  //로그인 실패
                {
                    count_login++;  //로그인 시도횟수 증가
                }

                break;

            case 2:  //메뉴 = 2. 회원정보 찾기
                fine_data();  //회원정보 찾기 함수실행

                break;

            case 3:  //메뉴 = 3. 임시 회원가입
                SignUp();  //임시 회원가입 함수실행

                break;

            case 4:  //메뉴 = 4. 프로그램 종료
                End();  //프로그램 종료 함수실행

                break;

            default:  //메뉴에 없는 항목
                printf("\n###올바른 메뉴를 입력하여주세요...\n");

//                sleep(2);

                End();  //종료 함수실행
        }
    }
}



int main2(void)  //메인2 함수 - 파일입출력 프로그램
{
    int choice[2];  //[0]메뉴선택, [1]파일선택

     while (1)
     {
        file_loading();  //파일 불러오기 함수실행

        choice[0] = menu();  //메뉴선택 함수실행

        switch (choice[0])
        {
            case 1:  //1.파일목록

                print_list();  //리스트 출력 함수실행
                break;

            case 2:  //2.파일열람
                choice[1] = file_choice("열람");  //파일선택 함수실헹
                file_read(choice[1]);  //파일열람 함수실행
                break;

            case 3:  //3.파일수정
                choice[1] = file_choice("수정");  //파일선택 함수실행
                file_edit(choice[1]);  //파일수정 함수실행
                break;

            case 4:  //4.파일 삭제
                choice[1] = file_choice("삭제");
                file_delete(choice[1]);  //파일삭제 함수실행
                break;

            case 5:  //5.파일 생성함수
                file_create();
                break;

            case 6:  //6.프로그램 종료
                file_save();  //파일저장 함수실행
                End();  //프로그램 종료 함수실행

            default:  //메뉴에 없는항목
                printf("\n###올바른 메뉴를 입력하여주세요...\n");
        }

         file_save();  //파일 저장함수 실행

         strcpy(add.file_name, "\0");

         count_file = 0;
         delete = -100;
         addition = 0;
    }

}















void print_menu(void)  //메뉴출력 함수
{
    printf("    ===============================\n");
    printf("        1. 로그인\n");
    printf("    ===============================\n");
    printf("        2. 회원정보 찾기\n");
    printf("    ===============================\n");
    printf("        3. 임시 회원가입\n");
    printf("    ===============================\n");
    printf("        4.프로그램 종료\n");
    printf("    ===============================\n>>> ");
}


int choice_menu(void)  //메뉴선택 함수
{
    int input;

    scanf("%d", &input);

    return(input);
}


int loginp(void)  //로그인 함수
{
    char input_ID[12] = { '\0' }, input_PW[12] = { '\0' };

    printf("***로그인화면***\n\n");
    printf("ID: ____________\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s", input_ID);
    printf("PW: ____________\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s", input_PW);

    for (int i = 0; i < count_member; i++)
    {
        if (strcmp(p[i].ID, input_ID) == 0 && strcmp(p[i].PW, input_PW) == 0)
        {
            printf("\n###로그인에 성공하셨습니다.\n");

//            sleep(3);

            return success;
        }
        else
        {
            if (i == (count_member - 1))  //마지막 구조체(회원)까지 검사했을 경우
            {
                printf("\n###회원정보가 일치하지 않습니다.\n");

//                sleep(3);

                return fail;
            }
            else  //마지막 구조체(회원)까지 검사하지 않았을 경우
            {
                continue;  //i를 증가시켜 다른회원 검사
            }
        }
    }

    return 0;
}


int fine_data(void)  //회원정보 찾기 함수
{
    char input_name[100], input_Email[40];
    int input_age, input_CallNumber, choice;

    printf("###회원정보 찾기를 진행합니다...###\n\n\n\n");
    printf("이름: ");
    scanf("%s", input_name);

    printf("나이: ");
    scanf("%d", &input_age);

    printf("핸드폰 번호: 010 ");
    scanf("%d", &input_CallNumber);

    printf("이메일 주소: ");
    scanf("%s", input_Email);

//    sleep(2);

    for (int i = 0; i < count_member; i++)
    {
        if (strcmp(p[i].Name, input_name) == 0 && (input_age == p[i].Age) && (input_CallNumber == p[i].CallNumber) && strcmp(p[i].Email, input_Email) == 0)
        {        //입력한 회원정보가 저장된 회원정보와 모든 항목이 일치할 경우

            printf("===================================\n");
            printf("%s님의  아이디 및 패스워드\n\n\n", p[i].Name);
            printf("ID: %s\n", p[i].ID);
            printf("PW: %s\n", p[i].PW);

            sleep(3);

            do
            {
                printf("\n    메뉴 화면으로 돌아가시려면 1을 입력하세요..\n\n");
                printf("    1. 메뉴 화면으로 돌아가기\n    >>> ");
                scanf("%d", &choice);

            } while (choice != 1);

            return 0;

        }
        else  //입력한 회원정보가 저장된 회원정보와 일치하지 않을 경우
        {
            if (i != (count_member - 1))  //마지막 회원까지 검사하지 않았을 경우
            {
                continue;  //i를 증가시켜 다른회원 검사
            }

            printf("\n\n일치하는 회원정보가 존재하지 않습니다.\n");

            sleep(3);

            printf("메뉴 화면으로 돌아갑니다...\n");

            sleep(1);

            return 0;
        }

    }
    return 0;
}


void SignUp(void)  //임시 회원가입 함수
{

    printf("###임시 회원가입을 진행합니다...");

//    sleep(2);
//    system("cls");

    printf("이용자님의 정보를 입력하여주세요...\n\n\n");
    printf("이름: ");
    scanf("%s", p[count_member].Name);

    printf("나이: ");
    scanf("%d", &p[count_member].Age);

    printf("핸드폰 번호: 010 ");
    scanf("%d", &p[count_member].CallNumber);

    printf("이메일 주소: ");
    scanf("%s", p[count_member].Email);

//    sleep(2);
//    system("cls");

    printf("사용하실 아이디와 패스워드를 입력하여주세요... **최대 12문자\n\n\n");
    printf("아이디: ");
    scanf("%s", p[count_member].ID);
    printf("패스워드: ");
    scanf("%s", p[count_member].PW);

//    Sleep(1500);

    printf("=======================================================\n\n");
    printf("회원가입이 완료되었습니다!!        #회원번호%d\n\n", count_member);
    printf("로그인을하여 회원페이지를 이용하실 수 있습니다.\n");

    count_member++;

//    Sleep(4000);
}
 

void login_delay(void)  //로그인 지연 함수
{
    printf("###로그인시도 초과로 인해 로그인이 잠시 지연됩니다.###\n\n\n");

    sleep(2);

    for (int i = 5; i > 0; i--)
    {
        printf("%d초 뒤 로그인지연이 해제됩니다...\n", i);

        sleep(1);
    }

    count_login = 0;  //로그인횟수 초기화
}











void file_loading(void)  //파일 불러오기 함수
{
    FILE *fp = NULL;

    fp = fopen("/Users/moontaeseo/Desktop/codeing/single/project/C/project(FileEdit)_01_c/manager_file", "r");
    if (fp == NULL)
    {
        printf("파일을 열 수 없습니다.. (에러코드 - 0)");
    }

    fscanf(fp, "%d", &count_file);   //관리자 파일에 저장된 사용자 파일의 개수

    for (int i = 0; i < count_file; i++)
    {
        fscanf(fp, "%s\n", file[i].file_name);
    }

    fclose(fp);

}

int menu(void)  //메뉴함수
{
    int choice;

    printf("실행하실 메뉴를 선택하여주세요..\n\n");
    printf("1. 파일목록\n");
    printf("2. 파일열람\n");
    printf("3. 파일수정\n");
    printf("4. 파일삭제\n");
    printf("5. 파일추가\n");
    printf("6. 프로그램 종료\n");

    scanf("%d", &choice);

    return(choice);
}


void print_list(void)  //리스트 출력함수
{
    printf("파일목록  ===================================\n\n");

    for (int i = 0; i < count_file; i++)
    {
        printf("%d.파일:  %s\n", i, file[i].file_name);
    }
}


int file_choice(char purpose[10])  //파일 선택함수
{
    int choice;

    do
    {
        printf("!! '-1'을 입력하면 파일목록 출력\n\n");
        printf("%s하실 파일의 번호를 입력하세요  >> ", purpose);
        scanf("%d", &choice);

        if (choice == -1)
        {
            print_list();
        }

    } while (choice == -1);

    return(choice);
}


void file_read(int choice)  //파일읽기 함수
{
    int a;
    FILE *fp = NULL;

    fp = fopen(file[choice].file_name, "r");
    if (fp == NULL)
    {
        printf("파일을 열 수 없었습니다.. (에러코드 - 1)");
    }

    printf("파일: %d. - %s\n================================\n", choice, file[choice].file_name);

    while ((a = fgetc(fp)) != EOF)
    {
        printf("%c", a);
    }

    printf("\n==========================================");

    printf("\n\n\n");

    fclose(fp);
}


void file_edit(int choice)  //파일 수정함수
{
    int input;

    printf("해당하는 번호를 입력하여주세요\n\n");
    printf("1. 내용 추가하기\n");
    printf("2. 내용 덮어쓰기\n");

    scanf("%d", &input);

    while(getchar() != '\n');  //입력버퍼 초기화

    if (input == 1)  //내용 추가하기
    {
        char ch[1000];

        FILE *fp = NULL;

        fp = fopen(file[choice].file_name, "a+, ccs=UTF-8");
        if (fp == NULL)
        {
            printf("파일을 열 수 없었습니다.. (에러코드 - 2)");
        }

        printf("파일 뒤에 추가하실 내용을 입력\n\n");

        fgets(ch, 1000, stdin);

        fprintf(fp, "%s", ch);

        printf("파일에 성공적으로 내용이 추가되었습니다.");


        fclose(fp);
    }
    else if (input == 2)  //내용 덮어쓰기
    {
        char ch[1000];

        FILE *fp = NULL;

        fp = fopen(file[choice].file_name, "w, ccs=UTF-8");
        if (fp == NULL)
        {
            printf("파일을 열 수 없었습니다.. (에러코드 - 3)");
        }

        printf("파일에 덮어쓰실 내용을 입력\n\n");
        fgets(ch, 1000, stdin);

        fprintf(fp, "%s", ch);

        fclose(fp);
   }
}


void file_delete(int choice)  //파일 삭제함수
{
    delete = choice;  //전역변수 - (삭제파일)
}


void file_create(void)  //파일 생성함수
{
    char ch[1000];

    while(getchar() != '\n');  //입력버퍼 초기화


    printf("생성하실 파일의 경로를 입력하여주세요..\n\n");
    scanf("%s", ch);

    strcpy(add.file_name, ch);

    ++addition;
}


void file_save(void)  //파일 저장함수
{
    FILE *fp = NULL;

    fp = fopen("/Users/moontaeseo/Desktop/codeing/single/project/C/project(FileEdit)_01_c/manager_file", "w");
    if (fp == NULL)
    {
        printf("파일을 열 수 없었습니다.. (에러코드 - 4)");
    }



    if (delete != -100)  //파일이 삭제되었을 때
    {

        fprintf(fp, "%d\n", (count_file - 1));

        for (int i = 0; i < count_file; i++)
        {
            if (i == delete)
            {
                continue;
            }
            else
            {
                fprintf(fp, "%s\n", file[i].file_name);
            }
        }

    }
    else if (addition != 0)  //파일이 추가되었을 때
    {

        fprintf(fp, "%d\n", (count_file + 1));

        for (int i = 0; i < count_file; i++)
        {
            fprintf(fp, "%s\n", file[i].file_name);
        }

        fprintf(fp, "%s\n", add.file_name);

    }
    else  //파일이 삭제, 추가되지 않았을 때
    {

        fprintf(fp, "%d\n", count_file);

        for (int i = 0; i <count_file; i++)
        {
            fprintf(fp, "%s\n", file[i].file_name);
        }

    }


    fclose(fp);

}


void End(void)  //프로그램 종료 함수
{
    for (int i = 5; i >= 0; i--)
    {
        printf("%d초 뒤에 종료됩니다...\n", i);

        sleep(1);
    }


    exit(0);  //프로세스 종료
}
