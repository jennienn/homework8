#include<stdio.h>
#include<stdlib.h>

typedef struct Node { /* 이중 연결 리스트의 노드를 정의 */
	int key; // 노드의 값
	struct Node* llink; // 왼쪽 링크 포인터
	struct Node* rlink; // 오른쪽 링크 포인터
} listNode;

int initialize(listNode** h); 
int freeList(listNode* h); 
int insertLast(listNode* h, int key); 
int deleteLast(listNode* h); 
int insertFirst(listNode* h, int key); 
int deleteFirst(listNode* h); 
int invertList(listNode* h); 

int insertNode(listNode* h, int key); 
int deleteNode(listNode* h, int key); 

void printList(listNode* h); 


int main()
{
	printf("[----- [김예진]  [2022041035] -----]\n"); 
	char command; // 입력받은 명령어를 저장하는 변수
    int key; // 입력받은 키 값을 저장하는 변수
    listNode* headnode=NULL; // linked list를 가리키는 head node를 NULL값으로 초기화


	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); 

		switch(command) { 
		case 'z': case 'Z': 
			initialize(&headnode); 
			break;
		case 'p': case 'P': 
			printList(headnode); 
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); 
			insertNode(headnode, key); 
			break;
		case 'd': case 'D': 
			printf("Your Key = ");
			scanf("%d", &key); 
			deleteNode(headnode, key); 
			break;
		case 'n': case 'N': 
			printf("Your Key = ");
			scanf("%d", &key); 
			insertLast(headnode, key); 
			break;
		case 'e': case 'E': 
			deleteLast(headnode);
			break; 
		case 'f': case 'F': 
			printf("Your Key = ");
			scanf("%d", &key); 
			insertFirst(headnode, key); 
			break;
		case 't': case 'T': 
			deleteFirst(headnode); 
			break;
		case 'r': case 'R': 
			invertList(headnode); 
			break;
		case 'q': case 'Q': 
			freeList(headnode); 
			break;
		default: 
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); 

	return 1;
}


int initialize(listNode** h) { // 리스트 노드를 초기화하는 함수
	// 헤드 노드가 NULL이 아니면, freeNode 함수를 호출하여 메모리를 해제함
	if (*h != NULL)
		freeList(*h);

	*h = (listNode*)malloc(sizeof(listNode)); // *h에 메모리를 할당함
	(*h)->rlink = *h; // h의 오른쪽 링크를 *h로 설정함
	(*h)->llink = *h; // h의 왼쪽 링크를 *h로 설정함
	(*h)->key = -9999; // h의 키 값을 -9999로 설정함
	return 1; // 함수 종료
}

int freeList(listNode* h){ // 리스트 노드를 해제하는 함수

	if (h->rlink == h) {//h의 rlink가 h를 가리키고 있다면
        free(h); // h를 해제
        return 1; 
}

listNode* p = h->rlink; // p를 h의 rlink로 초기화

listNode* prev = NULL; // prev를 NULL로 초기화
while (p != NULL && p != h) {// p가 NULL이 아니고 h가 아닐 때까지 반복
    prev = p; // prev를 p로 설정
    p = p->rlink; // p를 다음 노드로 이동
    free(prev); // prev를 해제
}
    free(h); // h를 해제
    return 0; 

}



void printList(listNode* h) { // 리스트 노드를 출력하는 함수
	int i = 0; // 변수 i를 0으로 초기화
	listNode* p; // listNode 포인터 p

	printf("\n---PRINT\n");

	if(h == NULL) { // h가 NULL인 경우
		printf("출력할 내용이 없습니다....\n"); // 아무 내용도 출력하지 않음
		return; // 함수 종료
	}

	p = h->rlink;// p를 h의 오른쪽 링크로 설정

	while(p != NULL && p != h) { // p가 NULL이 아니고 h가 아닌 동안 반복
		printf("[ [%d]=%d ] ", i, p->key); // i번째의 p의 키를 출력
		p = p->rlink; // p를 p의 오른쪽 링크로 설정
		i++; // i를 증가
	}
	printf("  items = %d\n", i); // 아이템의 개수를 출력

	printf("\n---checking addresses of links\n"); // 링크의 주소를 확인하는 부분
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); // head의 왼쪽 링크, head, 오른쪽 링크의 주소를 출력

	i = 0; // i를 0으로 초기화
	p = h->rlink; // p를 h의 다음 노드로 설정
	while(p != NULL && p != h) { // p가 NULL이 아니고 h가 아닌 동안 반복
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); // p의 i번째 키, 왼쪽 링크, 노드, 오른쪽 링크의 주소를 출력
		p = p->rlink;// p를 다음 노드로 설정
		i++; // i를 증가
	}
}


int insertLast(listNode* h, int key) {//list의 마지막에 key를 삽입하는 함수

	if (h == NULL) return -1; // h가 NULL인 경우 함수를 종료

    listNode* node = (listNode*)malloc(sizeof(listNode)); // listNode 포인터 변수 node를 동적으로 할당
    node->key = key; // node의 key 멤버에 전달된 key 값을 저장
    node->rlink = NULL; // node의 rlink를 NULL로 초기화
    node->llink = NULL; // node의 llink를 NULL로 초기화

    if (h->rlink == h) // h가 비어있는 경우 
    {
        h->rlink = node; // h의 rlink를 node로 설정
        h->llink = node; // h의 llink를 node로 설정
        node->rlink = h; // node의 rlink를 h로 설정
        node->llink = h; // node의 llink를 h로 설정
    } else {
        h->llink->rlink = node; // h의 llink의 rlink를 node로 설정
        node->llink = h->llink; // node의 llink를 h의 llink로 설정
        h->llink = node; // h의 llink를 node로 설정
        node->rlink = h; // node의 rlink를 h로 설정
    }

    return 1; 

}

int deleteLast(listNode* h) { // 리스트의 마지막 노드를 삭제하는 함수

    if (h->llink == h || h == NULL)
    {
        printf("삭제할 노드가 없습니다.\n");
        return 1; 
    }

    listNode* nodetoremove = h->llink; // 삭제할 노드를 nodetoremove에 저장 (마지막 노드)

    nodetoremove->llink->rlink = h; // nodetoremove의 llink의 rlink를 h로 설정하여 연결을 조정
    h->llink = nodetoremove->llink; // h의 llink를 nodetoremove의 llink로 설정 (마지막 노드 제거)

    free(nodetoremove); // nodetoremove 동적 메모리를 해제

    return 1; 

}

int insertFirst(listNode* h, int key)  {//리스트의 첫 번째에 key를 삽입하는 함수

    listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode 포인터 변수 node를 동적 할당
    node->key = key; //node의 key에 전달된 key 값을 저장
    node->rlink = NULL; //node의 rlink를 NULL로 초기화
    node->llink = NULL; //node의 llink를 NULL로 초기화

    node->rlink = h->rlink; //node의 rlink를 h의 rlink로 설정
    h->rlink->llink = node; //h의 rlink의 llink를 node로 설정
    node->llink = h; //node의 llink를 h로 설정
    h->rlink = node; //h의 rlink를 node로 설정

    return 1; 

}

int deleteFirst(listNode* h) {  // 리스트의 첫 번째 노드를 삭제하는 함수

	if (h == NULL || h->rlink == h) // 리스트가 비어있거나 리스트에 노드가 한 개인 경우
    {
        printf("삭제할 노드가 없습니다.\n"); 
        return 0; 
    }

    listNode* nodetoremove = h->rlink; // 삭제할 노드를 nodetoremove 변수에 저장

    nodetoremove->rlink->llink = h; // nodetoremove의 오른쪽 링크를 h와 연결
    h->rlink = nodetoremove->rlink; // h의 오른쪽 링크를 nodetoremove의 오른쪽 링크로 변경

    free(nodetoremove); // nodetoremove 노드를 메모리에서 해제

    return 1; 


}

int invertList(listNode* h) {// 리스트를 역순으로 변환하는 함수

	if (h->rlink == h || h == NULL) { // h의 오른쪽 링크가 h 자신이거나 h가 NULL인 경우,
		printf("역순으로 변환할 항목이 없습니다...\n");
		return 0;
	}

	listNode* n = h->rlink; // listNode 포인터 n은 h의 오른쪽 링크를 가리킴
	listNode* trail = h; // listNode 포인터 trail은 h를 가리킴
	listNode* middle = h; // listNode 포인터 middle은 h를 가리킴

	h->llink = h->rlink; // h의 왼쪽 링크는 h의 오른쪽 링크를 가리킴

	while (n != NULL && n != h) { // n이 NULL이 아니고 n이 h가 아닌 동안 반복
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->rlink = middle; 

	return 0;
}


int insertNode(listNode* h, int key) { 

	if(h == NULL) return -1;  // 만약 h가 NULL이면 오류를 반환

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드를 동적으로 할당
    node->key = key; // 노드의 key 값에 주어진 key 값을 할당
    node->llink = node->rlink = NULL; // 노드의 llink와 rlink를 NULL로 초기화

    if (h->rlink == h) { // h의 rlink가 h 자신을 가리키고 있다면 (리스트가 비어있는 경우)
        insertFirst(h, key); // insertFirst 함수를 호출하여 첫 번째 위치에 삽입
        return 1; 
    }

    listNode* n = h->rlink; // n을 h의 첫 번째 노드로 설정

    while (n != NULL && n != h) { // n이 NULL이거나 n이 h 자신을 가리키는 경우까지 반복
        if (n->key >= key) { // n의 key 값이 주어진 key 값보다 크거나 같다면 (삽입 위치를 찾은 경우)
            if (n == h->rlink) { // n이 h의 첫 번째 노드라면
                insertFirst(h, key); // insertFirst 함수를 호출하여 첫 번째 위치에 삽입
            } else {
                node->rlink = n; // node의 rlink를 n으로 설정
                node->llink = n->llink; // node의 llink를 n의 llink로 설정
                n->llink->rlink = node; // n의 llink의 rlink를 node로 설정
                n->llink = node; // n의 llink를 node로 설정
            }
            return 0; 
        }

        n = n->rlink; // n을 다음 노드로 이동
    }

    insertLast(h, key); // 삽입 위치를 찾지 못한 경우, 리스트의 마지막에 삽입
    return 0; 
}

int deleteNode(listNode* h, int key) { //key에 해당하는 노드를 삭제하는 함수

    if (h->rlink == h || h == NULL) { // h의 rlink가 h 자신을 가리키거나 h가 NULL인 경우
        printf("nothing to delete.\n");
        return 0;
    }

    listNode* n = h->rlink; // n을 h의 rlink로 초기화

    while (n != NULL && n != h) { // n이 NULL이 아니고 n이 h가 아닐 때까지 반복
        if (n->key == key) {
            // n의 key 값이 주어진 key와 같을 경우
            if (n == h->rlink) {
                // n이 h의 rlink와 같을 경우
                deleteFirst(h);
                // deleteFirst 함수를 호출하여 h의 첫 번째 노드를 삭제
            } else if (n->rlink == h) {
                // n의 rlink가 h와 같을 경우
                deleteLast(h);
                // deleteLast 함수를 호출하여 h의 마지막 노드를 삭제
            } else {
                n->llink->rlink = n->rlink;
                // n의 llink의 rlink를 n의 rlink로 설정
                n->rlink->llink = n->llink;
                // n의 rlink의 llink를 n의 llink로 설정
                free(n);
                // n 해제
            }
            return 0;
        }

        n = n->rlink;
        // n을 n의 rlink로 초기화
    }

    printf("cannot find the node for key = %d\n", key);
    return 0;
}

