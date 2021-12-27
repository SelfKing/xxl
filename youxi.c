#include "cj.h"



// 閾炬爤鍒濆鍖?  涓轰簡鍑忓皯 鎵嬪伐杈撳叆鍙兘甯︽潵鐨勯敊璇紝鎴戝喅瀹氶噰鐢ㄦ枃浠惰鍏ョ殑鏂瑰紡锛屾潵杩涜鍒濆鍖?
void init_stack() {
    stack_node.head = (node*)malloc(sizeof(node));
    stack_node.head->next = NULL;   // 寮勬槑鐧藉ご鎻掓硶锛岄渶瑕佺湅鏄庣櫧杩欓噷
    FILE *fp;
    if ((fp = fopen(GIFT_FILE, "r")) == NULL) {
        printf("榛樿鐨勭ぜ鐗╂枃浠朵笉瀛樺湪锛屽幓鎵惧埌瀹僜n");
        return ;
    }
    char name[MAXLEN];
    while((fscanf(fp, "%s", name)) != EOF) {
        node *n = (node *)malloc(sizeof(node));
        strcpy(n->g.name, name);   // 灏嗙ぜ鐗╂斁璧锋潵
        n->next = stack_node.head->next; // 寮勬槑鐧藉ご鎻掓硶锛岄渶瑕佺湅鏄庣櫧杩欓噷
        stack_node.head->next = n;  // 寮勬槑鐧藉ご鎻掓硶锛岄渶瑕佺湅鏄庣櫧杩欓噷
    }
    //printf("绀肩墿鍒濆鍖栧畬鎴怽n");
}

// 閾鹃槦鍒?
void init_queue() {
    queue_node.first = queue_node.last = (node *)malloc(sizeof(node));  // 寮勬噦閾鹃槦鍒楋紝鐪嬭繖閲?
    queue_node.first->next = NULL;   // 寮勬噦閾鹃槦鍒楋紝鐪嬭繖閲?
    FILE *fp;
    if ((fp = fopen(PEOPLE_FILE, "r")) == NULL) {
        printf("榛樿鐜╁鏂囦欢涓嶅瓨鍦╘n");
        return ;
    }
    char name[MAXLEN];
    while((fscanf(fp, "%s", name)) != EOF) {
        node *n = (node *)malloc(sizeof(node));
        strcpy(n->p.name, name);
        strcpy(n->g.name, nil);   // 鍏堟爣璁颁负绌?
        n->next = NULL;   // 寮勬噦閾鹃槦鍒楋紝鐪嬭繖閲?
        queue_node.last->next = n; //寮勬噦閾鹃槦鍒楋紝鐪嬭繖閲?
        queue_node.last = n;  // 寮勬噦閾鹃槦鍒楋紝鐪嬭繖閲?
    }
    //printf("鐜╁鍒濆鍖栧畬鎴怽n");
}

// 鎷垮埌涓€涓ぜ鐗?
node* get_gift() {
    node *n = stack_node.head->next;
    if(stack_node.head->next != NULL) {
        stack_node.head = stack_node.head->next;
    }
    return n;
}

int get_num() {

    int a = rand();
    return a % 10;
}

/********************************************************************/
List_User *initList_User(){
    
    List_User *list = (List_User *)malloc(sizeof(List_User));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;

    return list;
}//閾捐〃鍒濆鍖?

void addTail_User(List_User *list,people *data){
    
    NodeUser *node = (NodeUser *)malloc(sizeof(NodeUser));
    node->data = data;
    node->next = NULL;

    if(list->head == NULL){
        list->head = node;
    }else{
        list->tail->next = node;
    }
    list->tail = node;

    return;
}//澶存彃娉曟瀯寤洪摼琛? 

void Free_Userlist(NodeUser *list){

    NodeUser *tmp;
    while(list != NULL){
        tmp = list;
        list = list->next;
        free(tmp);
        tmp = NULL;
    }
    return;
}//閲婃斁閾捐〃 


void UserToFile_list(List_User *list){
    
    NodeUser *tmp = list->head;
    FILE *fp;
    fp = fopen(PEOPLE_FILE,"a");
    if (fp != NULL)
    {
        while(tmp != NULL){
            fprintf(fp, "%s\t", tmp->data->name);

            tmp = tmp->next;
        }
        fclose(fp);
    }else{
        printf("鏂囦欢淇濆瓨澶辫触 锛乗n");
    }
}

void Write_User(){
    system("clear");
    people *user;
    char flag = 'y';
    List_User *list = initList_User();
    while(flag == 'y'){
        user = Input_User_Data();
        addTail_User(list,user);
        printf("娣诲姞鎴愬姛 !\n");
        printf("鏄惁缁х画 y or n\n");
        getchar();
        flag = getchar();
        
    }
    UserToFile_list(list);
    Free_Userlist(list->head);

    return;
}
people *Input_User_Data(){
    char name[30];
    people *user = (people *)malloc(sizeof(people));
   
    printf("璇疯緭鍏ョ帺瀹禱n");
    scanf("%s",name);
    strcpy(user->name,name);

    return user;
}

void UserFromFile(List_User *list){
    FILE *fp;
    fp = fopen(PEOPLE_FILE, "r");
    if (fp != NULL)
    {
        while(!feof(fp)){
            people *user = (people *)malloc(sizeof(people));
            fscanf(fp,"%s",user->name);

            addTail_User(list,user);
        }

        fclose(fp);

    }else{
        printf("鏂囦欢鎵撳紑澶辫触 锛乗n");
    }
    return;
}


/***********************************************/


List_Gift *initList_Gift(){
    
    List_Gift *list = (List_Gift *)malloc(sizeof(List_Gift));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;

    return list;
}//閾捐〃鍒濆鍖?

void addTail_Gift(List_Gift *list,gift *data){
    
    NodeGift *node = (NodeGift *)malloc(sizeof(NodeGift));
    node->data = data;
    node->next = NULL;

    if(list->head == NULL){
        list->head = node;
    }else{
        list->tail->next = node;
    }
    list->tail = node;

    return;
}//澶存彃娉曟瀯寤洪摼琛? 

void Free_Giftlist(NodeGift *list){

    NodeGift *tmp;
    while(list != NULL){
        tmp = list;
        list = list->next;
        free(tmp);
        tmp = NULL;
    }
    return;
}//閲婃斁閾捐〃 


void GiftToFile_list(List_Gift *list){
    
    NodeGift *tmp = list->head;
    FILE *fp;
    fp = fopen(GIFT_FILE,"a");
    if (fp != NULL)
    {
        while(tmp != NULL){
            fprintf(fp, "%s\t", tmp->data->name);

            tmp = tmp->next;
        }
        fclose(fp);
    }else{
        printf("鏂囦欢淇濆瓨澶辫触 锛乗n");
    }
}

void Write_Gift(){
    system("clear");
    gift *g;
    char flag = 'y';
    List_Gift *list = initList_Gift();
    while(flag == 'y'){
        g = Input_Gift_Data();
        addTail_Gift(list,g);
        printf("娣诲姞鎴愬姛 !\n");
        printf("鏄惁缁х画 y or n\n");
        getchar();
        flag = getchar();
        
    }
    GiftToFile_list(list);
    Free_Giftlist(list->head);
}

gift *Input_Gift_Data(){
    char name[30];
    gift *g = (gift *)malloc(sizeof(gift));
   
    printf("璇疯緭鍏ョぜ鐗‐n");
    scanf("%s",name);
    strcpy(g->name,name);

    return g;
}

void GiftFromFile(List_Gift *list){
    FILE *fp;
    fp = fopen(GIFT_FILE, "r");
    if (fp != NULL)
    {
        while(!feof(fp)){
            gift *g = (gift *)malloc(sizeof(gift));
            fscanf(fp,"%s",g->name);

            addTail_Gift(list,g);
        }

        fclose(fp);

    }else{
        printf("鏂囦欢鎵撳紑澶辫触 锛乗n");
    }
    return;
}
/***********************************************************/

void display_User(){
    system("clear");
    char name[20];
    NodeUser *user;
    List_User *list = initList_User();
    UserFromFile(list);

    NodeUser *tmp = list->head;
    while(tmp->next != NULL){
            printf(" 鐜╁:%s\n",tmp->data->name);
            tmp = tmp->next;
        
    }
    Free_Userlist(list->head);
    return;
}

void display_Gift(){
    system("clear");
    char name[20];
    NodeGift *gift;
    List_Gift *list = initList_Gift();
    GiftFromFile(list);

    NodeGift *tmp = list->head;
    while(tmp->next != NULL){
            printf(" 濂栧搧:%s\n",tmp->data->name);
            tmp = tmp->next;
        
    }
    Free_Giftlist(list->head);
    return;
}






void play_game() {
    printf("娓告垙鐜板湪寮€濮媆n");
    int a, b;
    node *p = queue_node.first->next;
    while(p != NULL) {
        b = get_num();
        printf("璇?'%s' 寮€濮嬩粠0鍒?閲岄€変竴涓暟瀛?\n", p->p.name);
        scanf("%d", &a);
        if (a != b) {
            printf("杩欎釜鏁板瓧鏄細'%d' 涓嶅垢鐨勬槸锛岀帺瀹? : '%s'娌℃湁鐚滃埌!!\n", b, p->p.name);
        } else {
            node *g = get_gift();
            if (g != NULL) {
                strcpy(p->g.name, g->g.name);
                printf("鎭枩鐜╁: '%s', 鐚滃埌鏁板瓧:%d, 甯︾ぜ鐗╁洖瀹? '%s'!!!\n", p->p.name, b, g->g.name);
                free(g);
            } else {
                printf("瀵逛笉璧凤紝杩欓噷娌℃湁鏇村鐨勭ぜ鐗╀簡  锛岀幇鍦ㄩ€€鍑虹▼搴廫n");
                return ;
            }
        }
        p = p->next;
    }
    printf("娓告垙鐨勬渶鍚庯紝鎵€鏈夌殑鐜╁閮借閫変腑浜嗭紝姣忎釜浜洪€佷竴鐡跺彲涔怽n");
}


void User(){
    system("clear");
    init_queue();
    init_stack();
    //printf("--------------------娆㈣繋鏉ュ埌鎶藉娓告垙--------------------\n");
    printf("娓告垙瑙勫垯: \n");
    printf("绯荤粺浼氶殢鏈轰粠0鍒?閲岀敓鎴愪竴涓暟瀛楋紝濡傛灉浣犵寽瀵圭殑璇濓紝浣犱細寰楀埌濂栧搧锛屾瘡涓汉鍙兘閫変竴娆n");
    play_game();
    printf("--------------------娓告垙缁撴潫锛屽啀瑙侊紝璋㈣阿鍚勪綅鐨勫弬涓庯紒--------------------\n");

    return;
}


void Main_Menu(){
    system("clear");
    char flat;
    while(1){
        printf("1.寮€濮嬫娊濂朶n");
        printf("2.娣诲姞鐜╁\n");
        printf("3.娣诲姞濂栧搧\n");
        printf("4.鏌ョ湅鐜╁\n");
        printf("5.鏌ョ湅濂栧搧\n");
        printf("6.閫€鍑篭n");
        flat = getchar();
        switch(flat){
            case '1':   User();
                        printf("娓告垙缁撴潫 !\n");
                        printf("\n");
                        getchar();
                        getchar();
                        printf("璇锋寜浠绘剰閿繑鍥瀄n");
                        system("clear");
                        break;
            case '2':   Write_User();
                        getchar();
                        printf("璇锋寜浠绘剰閿繑鍥瀄n");
                        system("clear");
                        break;
            case '3':   Write_Gift();
                        getchar();
                        printf("璇锋寜浠绘剰閿繑鍥瀄n");
                        system("clear");
                        break;
            case '4':   display_User();
                        getchar();
                        getchar();
                        printf("璇锋寜浠绘剰閿繑鍥瀄n");
                        system("clear");
                        break;
            case '5':   display_Gift();
                        getchar();
                        getchar();
                        printf("璇锋寜浠绘剰閿繑鍥瀄n");
                        system("clear");
                        break;
            case '6':   system("clear");
                        return;
        }

    }


    return;
}
