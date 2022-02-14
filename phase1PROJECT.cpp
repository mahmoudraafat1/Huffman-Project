#include <iostream>

using namespace std;

class BTnode {
        public:
                char x[10000];
        int info;
        BTnode * pleft;
        BTnode * pright;
};
class cnode {
        public:
                char x[10000];
        int info = 1;
        cnode * pnext;
        BTnode * raddress;
};
class List1 {
        public:
                cnode * phead;
        cnode * ptail;
        List1() {
                phead = NULL;
                ptail = NULL;
        }
        void attach(cnode * pnn) {
                if (phead == NULL) {
                        phead = pnn;
                        ptail = pnn;
                } else {
                        ptail -> pnext = pnn;
                        ptail = pnn;
                }
        }
        void dispall() {
                cnode * ptrav;
                ptrav = phead;
                while (ptrav != NULL) {
                        cout << "[" << ptrav -> x << " / " << ptrav -> info << "]" << ' ';
                        ptrav = ptrav -> pnext;
                }
                cout << endl;
        }~List1() {
                cnode * ptmp;
                cnode * ptrav = phead;
                while (ptrav != NULL) {
                        ptmp = ptrav -> pnext;
                        delete ptrav;
                        ptrav = ptmp;
                }
        }
};
class cnode2 {
        public:
                char x;
        int * info;
        int size;
        cnode2 * pnext;
};
class List2 {
        public:
                cnode2 * phead;
        cnode2 * ptail;
        List2() {
                phead = NULL;
                ptail = NULL;
        }
        void attach(cnode2 * pnn) {
                if (phead == NULL) {
                        phead = pnn;
                        ptail = pnn;
                } else {
                        ptail -> pnext = pnn;
                        ptail = pnn;
                }
        }
        void dispall() {
                cnode2 * ptrav;
                ptrav = phead;
                while (ptrav != NULL) {
                        cout << "[" << ptrav -> x << " / ";
                        for (int i = 0; i < ptrav -> size; i++) cout << ptrav -> info[i];
                        cout << "]" << ' ';
                        ptrav = ptrav -> pnext;
                }
                cout << endl;

        }~List2() {
                cnode2 * ptmp;
                cnode2 * ptrav = phead;
                while (ptrav != NULL) {
                        ptmp = ptrav -> pnext;
                        delete ptrav;
                        ptrav = ptmp;
                }
        }
};
class BT {

        public:
                BTnode * proot;
        BT() {
                proot = NULL;
        }
        void insert(BTnode * pnn) {
                if (proot == NULL) proot = pnn;
                else {
                        BTnode * pb = NULL;
                        BTnode * pt = proot;
                        if (pt -> pleft != NULL && pt -> pright == NULL) pt -> pright = pnn;
                        else {
                                while (pt != NULL) {
                                        pb = pt;
                                        if (pnn -> info > pt -> info) pt = pt -> pright;
                                        else pt = pt -> pleft;
                                }
                                if (pnn -> info > pb -> info) pb -> pright = pnn;
                                else pb -> pleft = pnn;
                        }
                }
        }
        void disp(BTnode * pt) {
                if (pt == NULL) return;
                disp(pt -> pleft);
                cout << pt -> x << endl;
                cout << pt -> info << endl;
                disp(pt -> pright);
        }

        void dispall() {
                disp(proot);
        }

        void bye(BTnode * pt) {
                if (pt == NULL) return;
                bye(pt -> pleft);
                bye(pt -> pright);
                delete pt;
        }~BT() {
                bye(proot);
        }
};

void reading(List1 & L) {
        char letter[10000], check[10000];

        int F = 0, check_tool = 0, check_help = 0;

        cnode * pnn;
        cout << "type words being compreessed" << endl;
        cout << "_________________________________" << endl;
        cout<<endl;

        fgets(letter, sizeof(letter), stdin);

        check[0] = '\0';
        for (int i = 0; letter[i] != '\0'; i++) {
                for (int k = i + 1, check_help = 0; check[check_help] != '\0'; k++, check_help++) {
                        if (letter[i] == check[check_help]) {
                                F = 1;
                                break;
                        }
                }
                check[check_tool] = letter[i], check[check_tool + 1] = '\0', check_tool++;
                if (F == 0) {
                        pnn = new cnode;
                        pnn -> x[0] = letter[i], pnn -> x[1] = '\0';
                        pnn -> pnext = NULL, pnn -> raddress = NULL;
                        for (int k = i + 1; letter[k] != '\0'; k++) if (letter[i] == letter[k]) pnn -> info++;
                        L.attach(pnn);
                }
                F = 0;
        }
}
void arrange_isolate(List1 & L) {
        cnode * ptrav = L.phead, * ptrav2, * pb = NULL, * pb2, * ptemp;
        while (ptrav -> pnext != NULL) {
                ptrav2 = ptrav -> pnext, pb2 = ptrav;
                while (ptrav2 != NULL) {
                        if (ptrav2 -> info < ptrav -> info) {
                                if (ptrav == L.phead) {
                                        L.phead = ptrav2;
                                        pb2 -> pnext = ptrav2 -> pnext;
                                        ptrav2 -> pnext = ptrav;
                                        ptrav = ptrav2;
                                } else {
                                        pb -> pnext = ptrav2;
                                        pb2 -> pnext = ptrav2 -> pnext;
                                        ptrav2 -> pnext = ptrav;
                                        ptrav = ptrav2;
                                }
                        }
                        pb2 = ptrav2;
                        ptrav2 = ptrav2 -> pnext;
                }
                pb = ptrav;
                ptrav = ptrav -> pnext;
        }
        ptrav = L.phead;
        while (ptrav != NULL) {
                if (ptrav -> pnext == NULL) L.ptail = ptrav;
                ptrav = ptrav -> pnext;
        }
}
void combine(List1 & L, BT & Huffman_tree) {
        BTnode * pnnt;
        cnode * pnn, * ptrav1 = L.phead, * ptrav2 = ptrav1 -> pnext, * ptemp = L.phead;

        int comb = 0, F = 0;

        while (ptemp != NULL) {
                comb = 0, F = 0;
                pnn = new cnode;
                pnnt = new BTnode;
                for (int i = 0;; i++, comb++) {
                        if (ptrav1 -> x[i] == '\0') {
                                for (int k = 0;; k++, comb++) {
                                        if (ptrav2 -> x[k] == '\0') {
                                                pnnt -> x[comb] = ptrav2 -> x[k];
                                                pnn -> x[comb] = ptrav2 -> x[k];
                                                break;
                                        }
                                        pnnt -> x[comb] = ptrav2 -> x[k];
                                        pnn -> x[comb] = ptrav2 -> x[k];
                                }
                                break;
                        }
                        pnnt -> x[comb] = ptrav1 -> x[i];
                        pnn -> x[comb] = ptrav1 -> x[i];
                }
                pnnt -> info = ptrav1 -> info + ptrav2 -> info;
                pnn -> info = ptrav1 -> info + ptrav2 -> info;
                pnn -> pnext = NULL;
                pnnt -> pleft = NULL, pnnt -> pright = NULL;
                Huffman_tree.insert(pnnt);
                if (ptrav1 -> raddress != NULL && ptrav2 -> raddress != NULL) {
                        Huffman_tree.proot -> pleft = ptrav1 -> raddress, Huffman_tree.proot -> pright = ptrav2 -> raddress;
                        ptrav1 -> raddress = NULL, ptrav2 -> raddress = NULL;
                        F = 1;
                }
                if (ptrav1 -> raddress == NULL && ptrav2 -> raddress == NULL && F == 0) {
                        pnnt = new BTnode;
                        for (int i = 0;; i++) {
                                if (ptrav1 -> x[i] == '\0') {
                                        pnnt -> x[i] = ptrav1 -> x[i];
                                        break;
                                }
                                pnnt -> x[i] = ptrav1 -> x[i];
                        }
                        pnnt -> info = ptrav1 -> info;
                        pnnt -> pleft = NULL, pnnt -> pright = NULL;
                        Huffman_tree.insert(pnnt);
                        pnnt = new BTnode;
                        for (int i = 0;; i++) {
                                if (ptrav2 -> x[i] == '\0') {
                                        pnnt -> x[i] = ptrav2 -> x[i];
                                        break;
                                }
                                pnnt -> x[i] = ptrav2 -> x[i];
                        }
                        pnnt -> info = ptrav2 -> info;
                        pnnt -> pleft = NULL, pnnt -> pright = NULL;
                        Huffman_tree.insert(pnnt);
                        F = 1;
                }
                if (ptrav1 -> raddress == NULL && ptrav2 -> raddress != NULL && F == 0) {
                        Huffman_tree.proot -> pright = ptrav2 -> raddress;
                        pnnt = new BTnode;
                        for (int i = 0;; i++) {
                                if (ptrav1 -> x[i] == '\0') {
                                        pnnt -> x[i] = ptrav1 -> x[i];
                                        break;
                                }
                                pnnt -> x[i] = ptrav1 -> x[i];
                        }
                        pnnt -> info = ptrav1 -> info;
                        pnnt -> pleft = NULL, pnnt -> pright = NULL;
                        Huffman_tree.insert(pnnt);
                        F = 1;
                }
                if (ptrav1 -> raddress != NULL && ptrav2 -> raddress == NULL && F == 0) {
                        Huffman_tree.proot -> pleft = ptrav1 -> raddress;
                        pnnt = new BTnode;
                        for (int i = 0;; i++) {
                                if (ptrav2 -> x[i] == '\0') {
                                        pnnt -> x[i] = ptrav2 -> x[i];
                                        break;
                                }
                                pnnt -> x[i] = ptrav2 -> x[i];
                        }
                        pnnt -> info = ptrav2 -> info;
                        pnnt -> pleft = NULL, pnnt -> pright = NULL;
                        Huffman_tree.insert(pnnt);
                        F = 1;
                }
                pnn -> raddress = Huffman_tree.proot, Huffman_tree.proot = NULL;
                L.phead = ptrav2 -> pnext;
                ptemp = L.phead;
                L.attach(pnn);
                arrange_isolate(L);
                delete ptrav1;
                delete ptrav2;
                ptrav1 = L.phead, ptrav2 = ptrav1 -> pnext;
        }
        Huffman_tree.proot = L.phead -> raddress;
}
void count_BT(BTnode * pt, BTnode * & pb, cnode2 * & pnn, char y, int ct) {
        if (pt == NULL) {
                ct--;
                if (pb != NULL && pb -> x[0] == y && pb -> x[1] == '\0') {
                        pnn -> info = new int[ct];
                        pnn -> size = ct;
                        pb = NULL;
                }
                return;
        } else ct++;
        if (pt != NULL) pb = pt;
        count_BT(pt -> pleft, pb, pnn, y, ct);
        count_BT(pt -> pright, pb, pnn, y, ct);
}
void Traverse_BT(BTnode * proot, BTnode * pt, BTnode * & pb, cnode2 * & pnn, char y, int number, int comb, int & F) {
        if (pt == NULL) {
                if (pb != NULL && pb -> x[0] == y && pb -> x[1] == '\0' && F == 0) F = 1;
                return;
        }
        if (pt != NULL) pb = pt;
        
        if (F == 0 && pt != proot && comb < pnn -> size) {
                pnn -> info[comb] = number;
                comb++;
        }
        Traverse_BT(proot, pt -> pleft, pb, pnn, y, 0, comb, F);
        Traverse_BT(proot, pt -> pright, pb, pnn, y, 1, comb, F);
}

int main() {
        List1 L, L2;
        List2 L_2;
        BT Huffman_tree;
        cnode * pnn, * ptrav;

        reading(L);
        cout << endl;
        cout << "_________________________________" << endl;
        cout<<endl;
        cout << "The linked list" << endl;
        cout << "________________" << endl;
        cout<<endl;
        L.dispall();
        cout << "_______________________________________________________________" << endl;
        cout<<endl;
        arrange_isolate(L);
        cout << "The linked list sorted" << endl;
        cout << "_______________________" << endl;
        cout<<endl;
        L.dispall();
        cout << "_______________________________________________________________" << endl;
        cout<<endl;
        ptrav = L.phead;
        while (ptrav != NULL) {
                pnn = new cnode;
                for (int i = 0;; i++) {
                        if (ptrav -> x[i] == '\0') {
                                pnn -> x[i] = ptrav -> x[i];
                                break;
                        }
                        pnn -> x[i] = ptrav -> x[i];
                }
                pnn -> info = ptrav -> info;
                pnn -> pnext = NULL, pnn -> pnext = NULL;
                L2.attach(pnn);
                ptrav = ptrav -> pnext;
        }

        combine(L, Huffman_tree);
        
        cout << "The linked list combined" << endl;
        cout << "__________________________" << endl;
        cout<<endl;
        ptrav = L.phead;
        cout << "[" << ptrav -> x << " / " << ptrav -> info << "]" <<endl;
        // cout<<endl;
        //Huffman_tree.dispall();
        cout << "_______________________________________________________________" << endl;
        cout<<endl;
        int ct = 0, comb = 0, F = 0;
        ptrav = L2.phead;

        cnode2 * pnn2;
        BTnode * pb = L.phead -> raddress;

        while (ptrav) {
                ct = 0, comb = 0, F = 0;
                pnn2 = new cnode2;
                pb = L.phead -> raddress;
                count_BT(L.phead -> raddress, pb, pnn2, ptrav -> x[0], ct);
                pnn2 -> x = ptrav -> x[0];
                pb = L.phead -> raddress;
                Traverse_BT(L.phead -> raddress, L.phead -> raddress, pb, pnn2, ptrav -> x[0], 0, comb, F);
                pnn2 -> pnext = NULL;
                L_2.attach(pnn2);
                ptrav = ptrav -> pnext;
        }
        cout << "Letters with code" << endl;
        cout << "_______________________________________________________________" << endl;
        cout<<endl;
        L_2.dispall();
        cout<<endl;
        cout<<endl;
        
        return 0;
}