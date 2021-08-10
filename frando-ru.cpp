#include <stdio.h>
#include <windows.h>

void breakOut(int typeError) {//错误处理函数
    switch (typeError) {
    case 1:
        MessageBox(NULL, TEXT("错误1:这个错误很可能是文本指针操作不当造成的"), TEXT("frando-ru崩溃"), MB_OK);
        exit(1);
    case 2:
        MessageBox(NULL, TEXT("错误2:打开剪切板失败，可能是内存被锁定造成的"), TEXT("frando-ru崩溃"), MB_OK);
        exit(1);
    case 3:
        MessageBox(NULL, TEXT("错误3:剪切板内容不是CF_TXT，原因可能是frando-ru复制了图片文件"), TEXT("frando-ru崩溃"), MB_OK);
        exit(1);
    case 4:
        MessageBox(NULL, TEXT("错误4：没有找到包含目标群名称的文件"), TEXT("frando-ru错误"), MB_OK);
    }
}

void menu() {
    system("CLS");
    printf("说明书，现在就在开发所以还用不到哦\n回车退出");
    while (getchar() != '\n');
}

BOOL ToClipBoard(char* str)//剪切板写入数据
{
    OpenClipboard(0);
    EmptyClipboard();
    HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, strlen(str) + 1);
    if (!hg)
    {
        CloseClipboard();
        return false;
    }
    memcpy(GlobalLock(hg), str, strlen(str) + 1);
    GlobalUnlock(hg);
    SetClipboardData(CF_TEXT, hg);
    CloseClipboard();
    GlobalFree(hg);
    return true;
}

char* ReadClipBoard() {//剪切板读取数据
    HANDLE hclip;
    char* pbuf = NULL;
    if (OpenClipboard(NULL) == 0)
    {
        breakOut(2);
    }
    if (!IsClipboardFormatAvailable(CF_TEXT))
    {
        printf("剪切板当中的数据类型不匹配!\n");
        CloseClipboard();
        breakOut(3);
    }
    hclip = GetClipboardData(CF_TEXT);
    pbuf = (char*)GlobalLock(hclip);
    GlobalUnlock(hclip);
    //printf("%s\n", pbuf);
    CloseClipboard();
    return pbuf;
}

void dialog() //对话输出中心
{   
    FILE* fp0;
    fopen_s(&fp0, "dialogname.txt", "r");
    if (fp0 == NULL)
        breakOut(4);
    char windowName[50] = { 0 };
    fgets(windowName, sizeof(windowName) - 1, fp0);
    fclose(fp0);
    HWND dialog = FindWindowA(NULL, windowName);


    char fdialog[100] = "frando-ru还不能理解语言";
    if (!ToClipBoard(fdialog))
        breakOut(1);
    

    SendMessageA(dialog, WM_PASTE, 0, 0);
    SendMessageA(dialog, WM_KEYDOWN, VK_RETURN, 0);
}

void read() {//阅读文本的中心
    int count = 0;
    bool judge = 0;
    int judge0 = 0;
    char* read = ReadClipBoard();
    char sentence[500];
    char head[11] = {"@Frando-ru"};
    char toAnswer[100] = {};
ss:
    for (count=0;(*read!='\n')&&(*read!='\0');) {
        sentence[count] = *read;
        count++;
        read++;
    }
    sentence[count] = '\0';
    read++;
    for (count = 0; head[count] == sentence[count]; count++) {

    }
    if (count == 10) {
        for (count = 0; count < 101; count++) {
            toAnswer[count] = sentence[count];
        }
        judge = true;
        judge0 = 0;
    }
    if (judge)
        judge0++;
    if (*read != '\0')goto ss;
    if (strlen(toAnswer) != 0) {
        if (judge0 == 2) {
            printf("%s\n", toAnswer);
            dialog();//在这里植入对话的神经网络
        }   
    }
}


void main() {
    int i;
head:
    system("CLS");
    printf(">>欢迎来到frando-ru的终端>.<\n>>你想做什么呢？\n");
    scanf_s("%d", &i);
    switch (i) {
        case 1:
            break;
        case 2:
            menu();
            goto head;

    }
    //ShowWindow(FindWindow("ConsoleWindowClass", argv[0]),0);

    for (;;) {//主循环，这里包含了frando-ru的业务
    
    
    SetCursorPos(400, 400);
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    
    
    Sleep(1000);
    keybd_event(17, 0, 0, 0);
    keybd_event('A', 0, 0, 0);
    keybd_event(17, 0, 2, 0);
    keybd_event('A', 0, 2, 0);
    keybd_event(17, 0, 0, 0);
    keybd_event('C', 0, 0, 0);
    keybd_event(17, 0, 2, 0);
    keybd_event('C', 0, 2, 0);
    Sleep(1000);


    //system("CLS");
    //ReadClipBoard();//访问剪切板


    SetCursorPos(400, 700);
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(1000);
    SetCursorPos(1000, 400);
    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    Sleep(1000);


    read();//frando-ru对话发送
   

    Sleep(5000);//绝对不可以乱动的参数，时间较短可能会会导致鼠标不能控制，1秒并不足够关掉程序
    }
}