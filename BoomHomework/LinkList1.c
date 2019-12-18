#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>
/**结构体定义，头插法LA，尾插法LB
 */
typedef struct ListA
{
	int number;
	struct ListA* next;
}LA;
typedef struct ListB
{
	int number;
	struct ListB* next;
}LB;
/**函数声明部分
 */
/**创建链表函数
 */
void add(LA *LAHead, LB *LBHead);
void CreateListA(LA *LAHead);
void CreateListB(LB *LBHead);
void input(LA *LANow, LB *LBNow);
/**打印链表
 */
void PrintList(LA *LAHead, LB *LBHead);
/**打印单个节点
 */
void PrintOne(LA *LATarget, LB *LBTarget);
/**输出链表的长度
 */
void CountOfLinkList(LA *LAHead, LB *LBHead);
/**计算链表长度
 */
int CalculateLength(LA *LATar, LB *LBTar);
/**对链表进行操作，这里进行操作选择
 */
void OperateLinkList(LA *LAHead, LB *LBHead);
/**打印操作菜单
 */
void PrintOperateMenu();
/**检查链表是否为空
 */
int CheckList(LA *LAHead, LB *LBHead);
/**1.清空链表
 */
void ReleaseList(LA *LAHead, LB *LBHead);
/**清空一个链表
 */
void ReleaseListSingle(LA *AList, LB *BList);
/**2.修改链表节点数据
 */
void ModifyListPoint(LA *LAHead, LB *LBHead);
/**修改节点数值
 */
void ModifyMode(LA *LAHead, LB *LBHead, int pos, int list);
/**检查节点
 */
int CheckListPosition(LA *LAHead, LB *LBHead, int pos, int list);
/**3.查找指定数值x
 */
void SearchListValue(LA *LAHead, LB *LBHead);
/**搜索小模块
 */
LA *SearchListA(LA *LAHead);
LB *SearchListB(LB *LBHead);
/**4.向链表中插入节点
 */
void InsertListPoint(LA *LAHead, LB *LBHead);
/**插入函数
 */
/**头部
 */
void InsertHead(LA *LAHead, LB *LBHead);
/**尾部
 */
void InsertEnd(LA *LAHead, LB *LBHead);
/**指定位置
 */
int InsertPosition(LA *LAHead, LB *LBHead);
/**5.删除元素
 */
void DeleteList(LA *LAHead, LB *LBHead);
/**删除表头
 */
void DeleteListHead(LA *LAHead, LB *LBHead);
/**删除表尾
 */
void DeleteListEnd(LA *LAHead, LB *LBHead);
/**删除第pos个节点
 */
void DeleteListPos(LA *LAHead, LB *LBHead,int list);
/**删除值为x的第一个节点
 */
int DeleteListByValue(LA *LAHead, LB *LBHead);
/**6.交换两个节点的位置
 */
void ExchangePosition(LA *LAHead, LB *LBHead);
void Exchange(LA *LAHead, LB *LBHead, int pos[2]);
/**7.反转链表
 */
void ReverseList(LA *LAHead, LB *LBHead);
/**反转单个链表
 */
void ReverseListSingle(LA *LAHead, LB *LBHead);
/**打印菜单
 */
void PrintMenu()
{
	system("cls");
	printf("\t1.Create Link List      2.Print Link List\n"
		   "\t3.Operate Link List     4.Calculate the Number of Link List\n"
		   "\t0.Exit process          -1.Print Menu\n");
}
/**运行程序
 */
void running()
{
	int run = 1, doing, in;
	PrintMenu();
	LA *LAHead = (LA *)malloc(sizeof(LA));
	LB *LBHead = (LB *)malloc(sizeof(LB));
	if((!LAHead) || (!LBHead))
	{
		printf("Error!\n");
		exit(1);
	}
	LAHead->next = NULL;
	LBHead->next = NULL;
	while(run)
	{
		printf(">");
		in = scanf("%d", &doing);
		setbuf(stdin, NULL);
		if(!in)
		{
			printf("Unknown Construction!\n");
		}
		else
		{
			switch(doing)
			{
				case 1:add(LAHead, LBHead);break;
				case 2:PrintList(LAHead, LBHead);break;
				case 3:OperateLinkList(LAHead, LBHead);break;
                case 4:CountOfLinkList(LAHead, LBHead);break;
				case 0:run = 0;break;
				case -1:PrintMenu();
				default:printf("Wrong Construction!\n");break;
			}
		}
	}
	ReleaseListSingle(LAHead, NULL);
	ReleaseListSingle(NULL, LBHead);
	free(LAHead);
	free(LBHead);
	printf("Press any key to exit...");
	getchar();
}
int main(int argc, char *argv[])
{
	running();
	return 0;
}
/**add函数可以选择创建或添加链表A或B
 */
void add(LA *LAHead, LB *LBHead)
{
	int doing = 1, Do, in;
	printf("1.Insert Head to Create Link ListA\n"
		   "2.Insert End to Create Link ListB\n"
		   "3.Exit\n");
	while(doing)
	{
		printf(">");
		in = scanf("%d", &Do);
		if(!in)
		{
			printf("Unknown Construction!\n");
		}
		else
		{
			switch(Do)
			{
				case 1:CreateListA(LAHead);break;
				case 2:CreateListB(LBHead);break;
				case 3:doing = 0;printf("Exit Success!\n");break;
				default:printf("Wrong Construction!\n");
			}
		}
	}
}
/**创建链表A
 */
void CreateListA(LA *LAHead)
{
	LA *New = (LA *)malloc(sizeof(LA));
	if(!New)
	{
		printf("Error!\n");
		exit(0);
	}
	input(New, NULL);
	if(!LAHead->next)
	{
		LAHead->next = New;
		New->next = NULL;
	}
	else
	{
		LA *current = LAHead->next;
		LAHead->next = New;
		New->next = current;
	}
	printf("Create List A Success!\n");
}
/**创建链表B
 */
void CreateListB(LB *LBHead)
{
	LB* New = (LB*)malloc(sizeof(LB));
	if(!New)
	{
		printf("Error!\n");
		exit(0);
	}
	input(NULL, New);
	if(!LBHead->next)
	{
		LBHead->next = New;
	}
	else
	{
		LB *current = NULL;
		current = LBHead->next;
		while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = New;
	}
	New->next = NULL;
	printf("Create List B Success!\n");
}
/**输入函数，只能代入一个指针，同时另一个指针指向NULL
 */
void input(LA *LANow, LB *LBNow)
{
	if(((!LANow) && (!LBNow)) || (LANow != NULL && LBNow != NULL))
	{
		printf("Wrong!\nCan't input!\n");
		return;
	}
	printf("Input a number: ");
	if(!LANow)
	{
		scanf("%d", &LBNow->number);
	}
	else if(!LBNow)
	{
		scanf("%d", &LANow->number);
	}
}
/**打印链表A或B
 */
void PrintList(LA *LAHead, LB *LBHead)
{
    int doing = 1, choose, count = 0;
    if((!LAHead->next) && (!LBHead->next))
    {
        printf("Don't have any link!\nAlready return menu!\n");
        return;
    }
    printf("1.Print List A\t2.Print List B\n");
    while(doing)
    {
        printf("Choose List(-1 exit): ");
        scanf("%d", &choose);
        if(choose == -1)
        {
            doing = 0;
        }
        else if(choose == 1)
        {
            printf("List A\n");
            LA *LAcurrent = LAHead->next;
            while(LAcurrent != NULL)
            {
                printf(">%d.", ++count);
                PrintOne(LAcurrent, NULL);
                LAcurrent = LAcurrent->next;
            }
            count = 0;
        }
        else if(choose == 2)
        {
            printf("List B\n");
            LB *LBcurrent = LBHead->next;
            while(LBcurrent != NULL)
            {
                printf(">%d.", ++count);
                PrintOne(NULL, LBcurrent);
                LBcurrent = LBcurrent->next;
            }
            count = 0;
        }
        else
        {
            printf("Unknown!\n");
        }
    }
}
/**打印单个节点的函数，只能代入一个指针，同时另一个指针指向NULL
 */
void PrintOne(LA *LATarget, LB *LBTarget)
{
    if(((!LATarget) && (!LBTarget)) || (LATarget != NULL && LBTarget != NULL))
	{
		printf("Wrong!\nCan't print!\n");
		return;
	}
	printf("Number: ");
	if(!LATarget)
	{
		printf("%d\n", LBTarget->number);
	}
	else if(!LBTarget)
	{
		printf("%d\n", LATarget->number);
	}
}
/**输出链表的长度
 */
void CountOfLinkList(LA *LAHead, LB *LBHead)
{
    int count, choose;
    bool doing = true;
    if(CheckList(LAHead, LBHead))
    {
        return;
    }
    printf("1.Calculate Length of List A\n");
    printf("2.Calculate Length of List B\n");
    printf("3.Exit\n");
    while(doing)
    {
        printf("Choose: ");
        scanf("%d", &choose);
        setbuf(stdin, NULL);
        switch(choose)
        {
            case 1 : count = CalculateLength(LAHead, NULL);printf("Length of List A: %d\n", count);break;
            case 2 : count = CalculateLength(NULL, LBHead);printf("Length of List B: %d\n", count);break;
            case 3 : doing = false;break;
            default: printf("Wrong!\n");break;
        }
        count = 0;
    }
}

/**计算链表长度
 */
int CalculateLength(LA *LATar, LB *LBTar)
{
    int count = 0;
    if((!LATar))
    {
        LB *now = LBTar;
        while(now != NULL)
        {
            count++;
            now = now->next;
        }
    }
    else if((!LBTar))
    {
        LA *now = LATar;
        while(now != NULL)
        {
            count++;
            now = now->next;
        }
    }
    else
    {
        printf("Error!\n");
        return -1;
    }
    return count - 1;
}
/**打印操作菜单
 */
void PrintOperateMenu()
{
    system("cls");
    printf("\n\t1.Release Link List || 2.Modify List Point\n"
           "  \t3.Search Value      || 4.Insert List Point\n"
           "  \t5.Delete List Point || 6.Exchange List Point\n"
           "  \t7.Reverse List      || 0.Exit\n"
           "  \t-1.Show this Menu\n");
}
/**对链表进行操作，这里进行操作选择
 *(1) 1.清空链表X
 * 2.检查链表是否为空X
 * 3.1.返回pos节点的数据，超出范围结束程序
 *(2) 3.2.把pos节点的值修改为x的值，修改成功返回1，否则返回0
 *(3) 4.查找定值x的第一个节点，存在则返回地址，否则返回NULL
 *(4) 5.插入元素
 * 5.1.插在头部
 * 5.2.插在尾部
 * 5.3.插在pos节点，成功返回1，否则返回0
 *(5) 6.删除元素
 * 6.1.删除表头
 * 6.2.删除表尾
 * 6.3.删除第pos个节点
 * （删除失败结束程序）
 * 6.4.删除值为x的第一个节点，成功返回1，否则返回0
 *(6) 7.交换两个节点的位置
 *(7) 8.逆置单链表
 */
void OperateLinkList(LA *LAHead, LB *LBHead)
{
    bool doing = true;
    int choose;
    if(CheckList(LAHead, LBHead))
    {
        return;
    }
    PrintOperateMenu();
    while(doing)
    {
        printf("Choose: ");
        scanf("%d", &choose);
        switch(choose)
        {
            case 1 : ReleaseList(LAHead, LBHead);break;
            case 2 : ModifyListPoint(LAHead, LBHead);break;
            case 3 : SearchListValue(LAHead, LBHead);break;
            case 4 : InsertListPoint(LAHead, LBHead);break;
            case 5 : DeleteList(LAHead, LBHead);break;
            case 6 : ExchangePosition(LAHead, LBHead);break;
            case 7 : ReverseList(LAHead, LBHead);break;
            case -1: PrintOperateMenu();break;
            case 0 : doing = false;break;
            default:printf("Wrong!\n");break;
        }
        if(CheckList(LAHead, LBHead))
        {
            doing  = false;
        }
    }
    printf("Return Success!\n");
    PrintMenu();
}
/**检查链表是否为空
 */
int CheckList(LA *LAHead, LB *LBHead)
{
    if((!LAHead->next) || (!LBHead->next))
    {
        printf("Don't have any link!\nAlready return menu!\n");
        return 1;
    }
    return 0;
}
/**1.清空链表
 */
void ReleaseList(LA *LAHead, LB *LBHead)
{
    int choose;
    if(CheckList(LAHead, LBHead))
    {
        return;
    }
    printf("1.Release List A\n"
           "2.Release List B\n"
           "3.Return\n"
           "Choose: ");
    scanf("%d", &choose);
    switch(choose)
    {
        case 1 : ReleaseListSingle(LAHead, NULL);printf("Release Success!\n");break;
        case 2 : ReleaseListSingle(NULL, LBHead);printf("Release Success!\n");break;
        default: ;break;
    }
    printf("Return...\n");
}
/**清空一个链表
 */
void ReleaseListSingle(LA *AList, LB *BList)
{
    if(!AList)
    {
        LB *current = BList->next;
        BList->next = NULL;
        BList = current;
        while(BList != NULL)
        {
            current = BList;
            BList = BList->next;
            free(current);
        }
    }
    else if(!BList)
    {
        LA *current = AList->next;
        AList->next = NULL;
        AList = current;
        while(AList != NULL)
        {
            current = AList;
            AList = AList->next;
            free(current);
        }
    }
}

/**2.修改链表节点数据
 */
void ModifyListPoint(LA *LAHead, LB *LBHead)
{
    if(CheckList(LAHead, LBHead))
    {
        return;
    }
    bool doing = true;
    int list, pos, choose, number;
    printf("1.List A\n2.List B\n");
    while(doing)
    {
        printf("Choose List(-1 to exit): ");
        scanf("%d", &list);
        if(list == -1)
        {
            printf("Return...\n");
            return;
        }
        else if(list == 1 || list == 2)
        {
            doing = false;
        }
        else
        {
            printf("Wrong!\nAlready Return!\n");
            return;
        }
    }
    doing = true;
    while(doing)
    {
        printf("Input Position(-1 to exit): ");
        scanf("%d", &pos);
        if(pos == -1)
        {
            printf("Return...\n");
            return;
        }
        else
        {
            number = CheckListPosition(LAHead, LBHead, pos, list);
            if(number != 0)
            {
                doing = false;
            }
            else
            {
                printf("Error!\n");
                exit(1);
            }
        }
    }
    printf("1.Return Number\n"
           "2.Modify Number\n"
           "Others to exit\n");
    scanf("%d", &choose);
    switch(choose)
    {
        case 1 : printf("Position %d Number: %d\n", pos, number);break;
        case 2 : ModifyMode(LAHead, LBHead, pos, list);break;
        default: ;break;
    }
    printf("Return...\n");
}
/**检查节点
 */
int CheckListPosition(LA *LAHead, LB *LBHead, int pos, int list)
{
    int count = 1;
    if(pos <= 0)
    {
        printf("Error!\n");
        exit(1);
    }
    if(list == 1)
    {
        LA *current = LAHead->next;
        while(current != NULL)
        {
            if(pos == count)
            {
                return current->number;
            }
            current = current->next;
            count++;
        }
    }
    else if(list == 2)
    {
        LB *current = LBHead->next;
        while(current != NULL)
        {
            if(pos == count)
            {
                return current->number;
            }
            current = current->next;
            count++;
        }
    }
    return 0;
}
/**修改节点数值
 */
void ModifyMode(LA *LAHead, LB *LBHead, int pos, int list)
{
    int count = 1, num;
    if(pos <= 0)
    {
        printf("Error!\n");
        exit(1);
    }
    if(list == 1)
    {
        LA *current = LAHead->next;
        while(current != NULL)
        {
            if(pos == count)
            {
                break;
            }
            current = current->next;
            count++;
        }
        printf("New Number: ");
        scanf("%d", &num);
        current->number = num;
    }
    else if(list == 2)
    {
        LB *current = LBHead->next;
        while(current != NULL)
        {
            if(pos == count)
            {
                break;
            }
            current = current->next;
            count++;
        }
        printf("New Number: ");
        scanf("%d", &num);
        current->number = num;
    }
}
/**3.查找指定数值x
 */
void SearchListValue(LA *LAHead, LB *LBHead)
{
    bool doing = true;
    int choose;
    LA *LAsearch = NULL;
    LB *LBsearch = NULL;
    while(doing)
    {
        printf("1.List A\n2.List B\nOther.Exit\n$ ");
        scanf("%d", &choose);
        if(choose == 1)
        {
            LAsearch = SearchListA(LAHead);
            if(!LAsearch)
            {
                printf("Search Failed!\n");
            }
            else
            {
                printf("Address: 0x%p\n", LAsearch);
                PrintOne(LAsearch, NULL);
            }
        }
        else if(choose == 2)
        {
            LBsearch = SearchListB(LBHead);
            if(!LAsearch)
            {
                printf("Search Failed!\n");
            }
            else
            {
                printf("Address: 0x%p\n", LBsearch);
                PrintOne(NULL, LBsearch);
            }
        }
        else
        {
            doing = false;
        }
    }
    printf("Return...\n");
}
/**搜索小模块
 */
LA *SearchListA(LA *LAHead)
{
    LA *current = LAHead->next;
    int x;
    printf("Search: ");
    scanf("%d", &x);
    while(current != NULL)
    {
        if(current->number == x)
        {
            break;
        }
        current = current->next;
    }
    return current;
}
LB *SearchListB(LB *LBHead)
{
    LB *current = LBHead->next;
    int x;
    printf("Search: ");
    scanf("%d", &x);
    while(current != NULL)
    {
        if(current->number == x)
        {
            break;
        }
        current = current->next;
    }
    return current;
}
/**4.向链表中插入节点
 */
void InsertListPoint(LA *LAHead, LB *LBHead)
{
    bool doing = true;
    int list, choose, judge = 0;
    while(doing)
    {
        printf("1.List A\n2.List B\nOther.Exit\n$ ");
        scanf("%d", &list);
        if(list != 1 && list != 2)
        {
            doing = false;
            continue;
        }
        printf("Insert: 1.Head; 2.End; 3.Point position; Other.Exit\n$ ");
        scanf("%d", &choose);
        if(list == 1)
        {
            switch(choose)
            {
                case 1 : InsertHead(LAHead, NULL);printf("Insert Success!\n");break;
                case 2 : InsertEnd(LAHead, NULL);printf("Insert Success!\n");break;
                case 3 : judge = InsertPosition(LAHead, NULL);break;
                default: doing = false;break;
            }
            if(!judge)
            {
                return;
            }
            if(choose == 3 && judge == 1)
            {
                printf("Insert Success!\n");
            }
            else if(choose == 3 && (!judge))
            {
                return;
            }
        }
        else if(list == 2)
        {
            switch(choose)
            {
                case 1 : InsertHead(NULL, LBHead);printf("Insert Success!\n");break;
                case 2 : InsertEnd(NULL, LBHead);printf("Insert Success!\n");break;
                case 3 : judge = InsertPosition(NULL, LBHead);break;
                default: doing = false;break;
            }
            if(choose == 3 && judge == 1)
            {
                printf("Insert Success!\n");
            }
            else if(choose == 3 && (!judge))
            {
                return;
            }
        }
    }
}
/**插入函数
 */
/**头部
 */
void InsertHead(LA *LAHead, LB *LBHead)
{
    int number;
    printf("Number: ");
    scanf("%d", &number);
    if(!LAHead)
    {
        LB *current = (LB *)malloc(sizeof(LB));
        if(!current)
        {
            exit(1);
        }
        current->number = number;
        LB *previous = LBHead->next;
        if(!previous)
        {
            LBHead->next = current;
        }
        else
        {
            LBHead->next = current;
            current->next = previous;
        }
    }
    else if(!LBHead)
    {
        LA *current = (LA *)malloc(sizeof(LA));
        if(!current)
        {
            exit(1);
        }
        LA *previous = LAHead->next;
        current->number = number;
        LAHead->next = current;
        current->next = previous;
    }
}
/**尾部
 */
void InsertEnd(LA *LAHead, LB *LBHead)
{
    int number;
    printf("Number: ");
    scanf("%d", &number);
    if(!LAHead)
    {
        LB *previous = LBHead;
        while(previous->next != NULL)
        {
            previous = previous->next;
        }
        LB *current = (LB *)malloc(sizeof(LB));
        if(!current)
        {
            exit(1);
        }
        current->number = number;
        previous->next = current;
        current->next = NULL;
    }
    else if(!LBHead)
    {
        LA *previous = LAHead;
        while(previous->next != NULL)
        {
            previous = previous->next;
        }
        LA *current = (LA *)malloc(sizeof(LA));
        if(!current)
        {
            exit(1);
        }
        current->number = number;
        previous->next = current;
        current->next = NULL;
    }
}
/**指定位置
 */
int InsertPosition(LA *LAHead, LB *LBHead)
{
    int count = 0;
    if(!LAHead)
    {
        int pos;
        printf("Choose position: ");
        scanf("%d", &pos);
        if(!CheckListPosition(NULL, LBHead, pos, 2))
        {
            printf("Insert Failed!\nReturn...\n");
            return 0;
        }
        LB *current = LBHead->next;
        LB *previous = NULL;
        while(current != NULL)
        {
            if(pos == count)
            {
                break;
            }
            previous = current;
            current = current->next;
            count++;
        }
        LB *now = (LB *)malloc(sizeof(LB));
        previous->next = now;
        now->next = current;
        printf("Insert Number: ");
        scanf("%d", &now->number);
    }
    else if(!LBHead)
    {
        int pos;
        printf("Choose position: ");
        scanf("%d", &pos);
        if(!CheckListPosition(LAHead, NULL, pos, 1))
        {
            printf("Insert Failed!\nReturn...\n");
            return 0;
        }
        LA *current = LAHead->next;
        LA *previous = NULL;
        while(current != NULL)
        {
            if(pos == count)
            {
                break;
            }
            previous = current;
            current = current->next;
            count++;
        }
        LA *now = (LA *)malloc(sizeof(LA));
        previous->next = now;
        now->next = current;
        printf("Insert Number: ");
        scanf("%d", &now->number);
    }
    else
    {
        return 0;
    }
    return 1;
}
/**5.删除元素
 */
void DeleteList(LA *LAHead, LB *LBHead)
{
    bool doing = true;
    int list, choose, judge;
    while(doing)
    {
        printf("1.List A\n2.List B\nOther.Exit\n$ ");
        scanf("%d", &list);
        if(list != 1 && list != 2)
        {
            printf("Return...\n");
            return;
        }
        printf("Delete: 1.Head\n2.End\n3.Point position\n4.Point value\n$ ");
        scanf("%d", &choose);
        if(list == 1)
        {
            switch(choose)
            {
                case 1 : DeleteListHead(LAHead, NULL);printf("Delete Success!\n");break;
                case 2 : DeleteListEnd(LAHead, NULL);printf("Delete Success!\n");break;
                case 3 : DeleteListPos(LAHead, NULL, list);printf("Delete Success!\n");break;
                case 4 : judge = DeleteListByValue(LAHead, NULL);break;
                default: doing = false;break;
            }
            if(choose == 4 && judge == 1)
            {
                printf("Delete Success!\n");
            }
            else if(choose == 4 && (!judge))
            {
                printf("Delete Failed!\n");
                return;
            }
        }
        else if(list == 2)
        {
            switch(choose)
            {
                case 1 : DeleteListHead(NULL, LBHead);printf("Delete Success!\n");break;
                case 2 : DeleteListEnd(NULL, LBHead);printf("Delete Success!\n");break;
                case 3 : DeleteListPos(NULL, LBHead, list);printf("Delete Success!\n");break;
                case 4 : judge = DeleteListByValue(NULL, LBHead);break;
                default: doing = false;break;
            }
            if(choose == 4 && judge == 1)
            {
                printf("Delete Success!\n");
            }
            else if(choose == 4 && (!judge))
            {
                printf("Delete Failed!\n");
                return;
            }
        }
    }
}
/**删除表头
 */
void DeleteListHead(LA *LAHead, LB *LBHead)
{
    if(!LAHead)
    {
        LB *previous = LBHead;
        LB *current = LBHead->next;
        if(!current->next)
        {
            free(current);
            previous->next = NULL;
            return;
        }
        previous->next = current->next;
        free(current);
    }
    else if(!LBHead)
    {
        LA *previous = LAHead;
        LA *current = LAHead->next;
        if(!current->next)
        {
            free(current);
            previous->next = NULL;
            return;
        }
        previous->next = current->next;
        free(current);
    }
    return;
}
/**删除表尾
 */
void DeleteListEnd(LA *LAHead, LB *LBHead)
{
    if(!LAHead)
    {
        LB *current = LBHead->next;
        LB *previous = NULL;
        while(current->next != NULL)
        {
            previous = current;
            current = current->next;
        }
        if(!previous)
        {
            LBHead->next = NULL;
            free(current);
        }
        else
        {
            previous->next = NULL;
            free(current);
        }
    }
    else if(!LBHead)
    {
        LA *current = LAHead->next;
        LA *previous = NULL;
        while(current->next != NULL)
        {
            previous = current;
            current = current->next;
        }
        if(!previous)
        {
            LAHead->next = NULL;
            free(current);
        }
        else
        {
            previous->next = NULL;
            free(current);
        }
    }
}
/**删除第pos个节点
 */
void DeleteListPos(LA *LAHead, LB *LBHead, int list)
{
    int pos, count = 1;
    printf("Input Position(-1 to exit): ");
    scanf("%d", &pos);
    if(pos == -1)
    {
        return;
    }
    if(CheckListPosition(LAHead, LBHead, pos, list))
    {
        if(list == 1)
        {
            LA *previous = LAHead;
            LA *current = LAHead->next;
            LA *after = NULL;
            while(current != NULL)
            {
                if(pos == count)
                {
                    break;
                }
                previous = current;
                current = current->next;
                count++;
            }
            after = current->next;
            previous->next = after;
            free(current);
        }
        else if(list == 2)
        {
            LB *previous = LBHead;
            LB *current = LBHead->next;
            LB *after = NULL;
            while(current != NULL)
            {
                if(pos == count)
                {
                    break;
                }
                previous = current;
                current = current->next;
                count++;
            }
            after = current->next;
            previous->next = after;
            free(current);
        }
    }
    else
    {
        exit(1);
    }
}
/**删除值为x的第一个节点
 */
int DeleteListByValue(LA *LAHead, LB *LBHead)
{
    int value;
    printf("Input a number: ");
    scanf("%d", &value);
    if(!LBHead)
    {
        LA *previous = LAHead;
        LA *current = LAHead->next;
        LA *after = NULL;
        while(current != NULL)
        {
            if(current->number == value)
            {
                break;
            }
            previous = current;
            current = current->next;
        }
        if(!current)
        {
            printf("Don't have this number!\n");
            return 0;
        }
        else
        {
            after = current->next;
            previous->next = after;
            free(current);
        }
    }
    else if(!LAHead)
    {
        LB *previous = LBHead;
        LB *current = LBHead->next;
        LB *after = NULL;
        while(current != NULL)
        {
            if(current->number == value)
            {
                break;
            }
            previous = current;
            current = current->next;
        }
        if(!current)
        {
            printf("Don't have this number!\n");
            return 0;
        }
        else
        {
            after = current->next;
            previous->next = after;
            free(current);
        }
    }
    return 1;
}
/**6.交换两个节点的位置
 */
void ExchangePosition(LA *LAHead, LB *LBHead)
{
    bool doing = true;
    int list, pos[2];
    while(doing)
    {
        printf("1.List A\n2.List B\nOther.Exit\n$ ");
        scanf("%d", &list);
        if(list != 1 && list != 2)
        {
            printf("Return...\n");
            return;
        }
        if(list == 1)
        {
            printf("Position 1: ");
            scanf("%d", &pos[0]);
            if(!CheckListPosition(LAHead, LBHead, pos[0], list) || pos[0] <= 0)
            {
                printf("Don't have this position!\n");
                printf("Return...\n");
                return;
            }
            printf("Position 2: ");
            scanf("%d", &pos[1]);
            if(!CheckListPosition(LAHead, LBHead, pos[1], list) || pos[1] <= 0)
            {
                printf("Don't have this position!\n");
                printf("Return...\n");
                return;
            }
            if(pos[0] == pos[1])
            {
                printf("Exchange success!\n");
                continue;
            }
            if(pos[0] > pos[1])
            {
                printf("Position 2 should be behind Position 1!\n");
            }
            Exchange(LAHead, NULL, pos);
            printf("Exchange success!\n");
        }
        else if(list == 2)
        {
            printf("Position 1: ");
            scanf("%d", &pos[0]);
            if(!CheckListPosition(LAHead, LBHead, pos[0], list) || pos[0] <= 0)
            {
                printf("Don't have this position!\n");
                printf("Return...\n");
                return;
            }
            printf("Position 2: ");
            scanf("%d", &pos[1]);
            if(!CheckListPosition(LAHead, LBHead, pos[1], list) || pos[1] <= 0)
            {
                printf("Don't have this position!\n");
                printf("Return...\n");
                return;
            }
            if(pos[0] == pos[1])
            {
                printf("Exchange success!\n");
                continue;
            }
            if(pos[0] > pos[1])
            {
                printf("Position 2 should be behind Position 1!\n");
            }
            Exchange(NULL, LBHead, pos);
            printf("Exchange success!\n");
        }
    }
}
void Exchange(LA *LAHead, LB *LBHead, int pos[2])
{
    int count = 1;
    if(!LBHead)
    {
        LA *current1 = LAHead->next;
        LA *previous1 = LAHead;
        LA *after1 = NULL;
        while(current1 != NULL)
        {
            if(pos[0] == count)
            {
                break;
            }
            previous1 = current1;
            current1 = current1->next;
            count++;
        }
        after1 = current1->next;
        count = 1;
        LA *current2 = LAHead->next;
        LA *previous2 = LAHead;
        LA *after2 = NULL;
        while(current2 != NULL)
        {
            if(pos[1] == count)
            {
                break;
            }
            previous2 = current2;
            current2 = current2->next;
            count++;
        }
        after2 = current2->next;
        if(previous2 == current1)
        {
            previous1->next = current2;
            current2->next = current1;
            current1->next = after2;
            return;
        }
        previous2->next = current1;
        current1->next = after2;
        previous1->next = current2;
        current2->next = after1;
    }
    else if(!LAHead)
    {
        LB *current1 = LBHead->next;
        LB *previous1 = LBHead;
        LB *after1 = NULL;
        while(current1 != NULL)
        {
            if(pos[0] == count)
            {
                break;
            }
            previous1 = current1;
            current1 = current1->next;
            count++;
        }
        after1 = current1->next;
        count = 1;
        LB *current2 = LBHead->next;
        LB *previous2 = LBHead;
        LB *after2 = NULL;
        while(current2 != NULL)
        {
            if(pos[1] == count)
            {
                break;
            }
            previous2 = current2;
            current2 = current2->next;
            count++;
        }
        after2 = current2->next;
        if(previous2 == current1)
        {
            previous1->next = current2;
            current2->next = current1;
            current1->next = after2;
            return;
        }
        previous2->next = current1;
        current1->next = after2;
        previous1->next = current2;
        current2->next = after1;
    }
}
/**7.反转链表
 */
void ReverseList(LA *LAHead, LB *LBHead)
{
    int list;
    printf("1.List A\n2.List B\nOther.exit\n");
    printf("$ ");
    scanf("%d", &list);
    if(list == 1)
    {
        ReverseListSingle(LAHead, NULL);
    }
    else if(list == 2)
    {
        ReverseListSingle(NULL, LBHead);
    }
    printf("Return...\n");
}
/**反转单个链表
 */
void ReverseListSingle(LA *LAHead, LB *LBHead)
{
    if(!LAHead)
    {
        if(LBHead->next != NULL || LBHead->next->next != NULL)
        {
            LB *temp;
            LB *head = LBHead->next;
            LB *previous = LBHead->next->next;
            LB *current = LBHead->next->next->next;
            previous->next = head;
            head->next = NULL;
            while(current != NULL)
            {
                temp = current->next;
                current->next = previous;
                previous = current;
                current = temp;
            }
            LBHead->next = previous;
        }
    }
    else if(!LBHead)
    {
        if(LAHead->next != NULL || LAHead->next->next != NULL)
        {
            LA *temp;
            LA *head = LAHead->next;
            LA *previous = LAHead->next->next;
            LA *current = LAHead->next->next->next;
            previous->next = head;
            head->next = NULL;
            while(current != NULL)
            {
                temp = current->next;
                current->next = previous;
                previous = current;
                current = temp;
            }
            LAHead->next = previous;
        }
    }
    printf("Reverse Success!\n");
}
