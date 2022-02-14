#include <iostream>

#include <fstream>

#include <string>

#include <stdio.h>

using namespace std;
class ctnode {
        public:
                char x[1000];
        int info;
        ctnode * pleft;
        ctnode * pright;
};
class cnode {
        public:
                char x[1000];
        int info = 1;
        cnode * pnext;
        ctnode * raddress;
};
class cList {
        public:
                cnode * phead;
        cnode * ptail;
        cList() {
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
                        cout << "(" << ptrav -> x << ", " << ptrav -> info << ")" << ' ';
                        ptrav = ptrav -> pnext;
                }
                cout << endl;
        }~cList() {
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
class cList2 {
        public:
                cnode2 * phead;
        cnode2 * ptail;
        cList2() {
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
                        cout << "(" << ptrav -> x << ", ";
                        for (int i = 0; i < ptrav -> size; i++) {
                                cout << ptrav -> info[i];
                        }
                        cout << ")" << ' ';
                        ptrav = ptrav -> pnext;
                }
                cout << endl;
        }~cList2() {
                cnode2 * ptmp;
                cnode2 * ptrav = phead;
                while (ptrav != NULL) {
                        ptmp = ptrav -> pnext;
                        delete ptrav;
                        ptrav = ptmp;
                }
        }
};
class cbstree {
        public:
                ctnode * proot;
        cbstree() {
                proot = NULL;
        }
        void insert(ctnode * pnn) {
                if (proot == NULL) {
                        proot = pnn;
                } else {
                        ctnode * pb = NULL;
                        ctnode * pt = proot;
                        if (pt -> pleft != NULL && pt -> pright == NULL) {
                                pt -> pright = pnn;
                        } else {
                                while (pt != NULL) {
                                        pb = pt;
                                        if (pnn -> info > pt -> info) {
                                                pt = pt -> pright;
                                        } else {
                                                pt = pt -> pleft;
                                        }
                                }
                                if (pnn -> info > pb -> info) {
                                        pb -> pright = pnn;
                                } else {
                                        pb -> pleft = pnn;
                                }
                        }
                }
        }
        void disp(ctnode * pt) {
                if (pt == NULL) {
                        return;
                }
                disp(pt -> pleft);
                cout << pt -> x << endl;
                cout << pt -> info << endl;
                disp(pt -> pright);
        }
        void dispall() {
                disp(proot);
        }
        void bye(ctnode * pt) {
                if (pt == NULL) {
                        return;
                }
                bye(pt -> pleft);
                bye(pt -> pright);
                delete pt;
        }~cbstree() {
                bye(proot);
        }
};

void reading(cList & L, char letter[]) {
        char check[10000];
        int i, k, flag = 0, drivercheck = 0, driverloop = 0;
        cnode * pnn;
        ifstream xfile;
        xfile.open("/home/mahmoud-raafat/Downloads/example.txt");
        if (xfile.is_open()) {
                string line;
                while (getline(xfile, line)) {
                        for (i = 0; i < line.length(); i++) {
                                letter[i] = line[i];
                        }
                        letter[i] = '\0';
                }
        }
        cout << letter;
        cout << endl;
        xfile.close();
        check[0] = '\0';
        for (i = 0; letter[i] != '\0'; i++) {
                for (k = i + 1, driverloop = 0; check[driverloop] != '\0'; k++, driverloop++) {
                        if (letter[i] == check[driverloop]) {
                                flag = 1;
                                break;
                        }
                }
                check[drivercheck] = letter[i], check[drivercheck + 1] = '\0', drivercheck++;
                if (flag == 0) {
                        pnn = new cnode;
                        pnn -> x[0] = letter[i], pnn -> x[1] = '\0';
                        pnn -> pnext = NULL, pnn -> raddress = NULL;
                        for (k = i + 1; letter[k] != '\0'; k++) {
                                if (letter[i] == letter[k]) {
                                        pnn -> info++;
                                }
                        }
                        L.attach(pnn);
                }
                flag = 0;
        }
}
void arrange_isolate(cList & L) {
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
                if (ptrav -> pnext == NULL) {
                        L.ptail = ptrav;
                }
                ptrav = ptrav -> pnext;
        }
}
void combine(cList & L, cbstree & tree) {
        ctnode * pnnt;
        cnode * pnn, * ptrav1 = L.phead, * ptrav2 = ptrav1 -> pnext, * ptemp = L.phead;
        int i, k, driver = 0, flag = 0;
        while (ptemp != NULL) {
                driver = 0, flag = 0;
                pnn = new cnode;
                pnnt = new ctnode;
                for (i = 0;; i++, driver++) {
                        if (ptrav1 -> x[i] == '\0') {
                                for (k = 0;; k++, driver++) {
                                        if (ptrav2 -> x[k] == '\0') {
                                                pnnt -> x[driver] = ptrav2 -> x[k];
                                                pnn -> x[driver] = ptrav2 -> x[k];
                                                break;
                                        }
                                        pnnt -> x[driver] = ptrav2 -> x[k];
                                        pnn -> x[driver] = ptrav2 -> x[k];
                                }
                                break;
                        }
                        pnnt -> x[driver] = ptrav1 -> x[i];
                        pnn -> x[driver] = ptrav1 -> x[i];
                }
                pnnt -> info = ptrav1 -> info + ptrav2 -> info;
                pnn -> info = ptrav1 -> info + ptrav2 -> info;
                pnn -> pnext = NULL;
                pnnt -> pleft = NULL, pnnt -> pright = NULL;
                tree.insert(pnnt);
                if (ptrav1 -> raddress != NULL && ptrav2 -> raddress != NULL) {
                        tree.proot -> pleft = ptrav1 -> raddress, tree.proot -> pright = ptrav2 -> raddress;
                        ptrav1 -> raddress = NULL, ptrav2 -> raddress = NULL;
                        flag = 1;
                }
                if (ptrav1 -> raddress == NULL && ptrav2 -> raddress == NULL && flag == 0) {
                        pnnt = new ctnode;
                        for (i = 0;; i++) {
                                if (ptrav1 -> x[i] == '\0') {
                                        pnnt -> x[i] = ptrav1 -> x[i];
                                        break;
                                }
                                pnnt -> x[i] = ptrav1 -> x[i];
                        }
                        pnnt -> info = ptrav1 -> info;
                        pnnt -> pleft = NULL, pnnt -> pright = NULL;
                        tree.insert(pnnt);
                        pnnt = new ctnode;
                        for (i = 0;; i++) {
                                if (ptrav2 -> x[i] == '\0') {
                                        pnnt -> x[i] = ptrav2 -> x[i];
                                        break;
                                }
                                pnnt -> x[i] = ptrav2 -> x[i];
                        }
                        pnnt -> info = ptrav2 -> info;
                        pnnt -> pleft = NULL, pnnt -> pright = NULL;
                        tree.insert(pnnt);
                        flag = 1;
                }
                if (ptrav1 -> raddress == NULL && ptrav2 -> raddress != NULL && flag == 0) {
                        tree.proot -> pright = ptrav2 -> raddress;
                        pnnt = new ctnode;
                        for (i = 0;; i++) {
                                if (ptrav1 -> x[i] == '\0') {
                                        pnnt -> x[i] = ptrav1 -> x[i];
                                        break;
                                }
                                pnnt -> x[i] = ptrav1 -> x[i];
                        }
                        pnnt -> info = ptrav1 -> info;
                        pnnt -> pleft = NULL, pnnt -> pright = NULL;
                        tree.insert(pnnt);
                        flag = 1;
                }
                if (ptrav1 -> raddress != NULL && ptrav2 -> raddress == NULL && flag == 0) {
                        tree.proot -> pleft = ptrav1 -> raddress;
                        pnnt = new ctnode;
                        for (i = 0;; i++) {
                                if (ptrav2 -> x[i] == '\0') {
                                        pnnt -> x[i] = ptrav2 -> x[i];
                                        break;
                                }
                                pnnt -> x[i] = ptrav2 -> x[i];
                        }
                        pnnt -> info = ptrav2 -> info;
                        pnnt -> pleft = NULL, pnnt -> pright = NULL;
                        tree.insert(pnnt);
                        flag = 1;
                }
                pnn -> raddress = tree.proot, tree.proot = NULL;
                L.phead = ptrav2 -> pnext;
                ptemp = L.phead;
                L.attach(pnn);
                arrange_isolate(L);
                delete ptrav1;
                delete ptrav2;
                ptrav1 = L.phead, ptrav2 = ptrav1 -> pnext;
        }
        tree.proot = L.phead -> raddress;
}
void count_BT(ctnode * pt, ctnode * & pb, cnode2 * & pnn, char y, int ct) {
        if (pt == NULL) {
                ct--;
                if (pb != NULL && pb -> x[0] == y && pb -> x[1] == '\0') {
                        pnn -> info = new int[ct];
                        pnn -> size = ct;
                        pb = NULL;
                }
                return;
        } else {
                ct++;
        }
        if (pt != NULL) {
                pb = pt;
        }
        count_BT(pt -> pleft, pb, pnn, y, ct);
        count_BT(pt -> pright, pb, pnn, y, ct);
}
void traverse_BT(ctnode * proot, ctnode * pt, ctnode * & pb, cnode2 * & pnn, char y, int number, int driver, int & flag) {
        if (pt == NULL) {
                if (pb != NULL && pb -> x[0] == y && pb -> x[1] == '\0' && flag == 0) {
                        flag = 1;
                }
                return;
        }
        if (pt != NULL) {
                pb = pt;
        }
        if (flag == 0 && pt != proot && driver < pnn -> size) {
                pnn -> info[driver] = number;
                driver++;
        }
        traverse_BT(proot, pt -> pleft, pb, pnn, y, 0, driver, flag);
        traverse_BT(proot, pt -> pright, pb, pnn, y, 1, driver, flag);
}

void Compress(cList2 & L_Encode, char letter[], char savecompress[], int & save_ct, int & check_zero) {
        ofstream compressed_file;
        cnode2 * ptrav = L_Encode.phead;
        char x = 0, m = 1;
        int k, i, ct = 0, driver = 0;
        int binary[8];
        compressed_file.open("/home/mahmoud-raafat/Downloads/Compressed.txt", ios::trunc);
        if (compressed_file.is_open()) {
                cout << "File is open" << endl;
                cout << "________________________________" << endl;
                cout << "Compressed text" << endl;
                cout << "________________________________" << endl;
                for (i = 0; letter[i] != '\0'; i++) {
                        ptrav = L_Encode.phead;
                        while (ptrav != NULL) {
                                if (letter[i] == ptrav -> x) {
                                        for (k = 0; k < ptrav -> size; k++) {
                                                if (ptrav -> info[k] == 1) {
                                                        x = x | (m << ct);
                                                }
                                                ct++;
                                                if (ct == 8) {
                                                        ct = 0;
                                                        cout << x;
                                                        savecompress[driver] = x;
                                                        driver++;
                                                        compressed_file << x;
                                                        x = 0;
                                                }
                                        }
                                }
                                ptrav = ptrav -> pnext;
                        }
                }
                if (ct > 0) {
                        savecompress[driver] = x;
                        cout << x;
                        compressed_file << x;
                        save_ct = ct;
                        if (x == 0 && ct > 0) {
                                check_zero = 0;
                                savecompress[driver] = '\0';
                        } else {
                                savecompress[driver + 1] = '\0';
                        }
                } else {
                        savecompress[driver] = '\0';
                }
                compressed_file.close();
        } else {
                cout << "File is not open" << endl;
                cout << "________________________________" << endl;
        }
        cout << endl;
        cout << "________________________________" << endl;
}
void Decompress(cList2 & L_Encode, char savecompress[], int & save_ct, int & check_zero) {
        ifstream compressed_file;
        ofstream decompressed_file;
        cnode2 * ptrav = L_Encode.phead;
        char m = 1, res;
        int i, k, j, ct = 0, shift = 0, driver = 0, range = 8, flag = 0;
        int binary[100];
        compressed_file.open("/home/mahmoud-raafat/Downloads/Compressed.txt");
        compressed_file.close();
        cout << "________________________________" << endl;
        cout << "Copied compressed text" << endl;
        cout << "________________________________" << endl;
        cout << savecompress << endl;
        cout << "_________________________" << endl;
        decompressed_file.open("/home/mahmoud-raafat/Downloads/Decompressed.txt", ios::trunc);
        cout << "Decompressed text" << endl;
        cout << "________________________________" << endl;
        if (decompressed_file.is_open()) {
                cout << "________________________________" << endl;
                cout << "Decompressed file is open" << endl;
                cout << "________________________________" << endl;
                for (int i = 0 ; ; i++) {
                        if (check_zero == 1 && savecompress[i] == '\0') {
                                break;
                        }
                        if (check_zero == 0 && savecompress[i] == '\0' && save_ct > 0) {
                                range = save_ct;
                                flag = 1;
                        } else {
                                if (check_zero == 1 && savecompress[i + 1] == '\0' && save_ct > 0) {
                                        range = save_ct;
                                        flag = 1;
                                }
                        }
                        for (int j = 0; j < range; j++) {
                                res = savecompress[i] & (m << shift);
                                shift++;
                                if (res != 0) {
                                        binary[driver] = 1;
                                        driver++;
                                } else {
                                        binary[driver] = 0;
                                        driver++;
                                }
                                if (shift == 8) {
                                        shift = 0;
                                }
                                res = 0;
                                ptrav = L_Encode.phead;
                                while (ptrav != NULL) {
                                        if (driver == ptrav -> size) {
                                                for (int k = 0; k < ptrav -> size; k++) {
                                                        if (ptrav -> info[k] == binary[k]) {
                                                                ct++;
                                                        } else {
                                                                ct = 0;
                                                        }
                                                }
                                                if (ptrav -> size == ct) {
                                                        ct = 0;
                                                        cout << ptrav -> x;
                                                        decompressed_file << ptrav -> x;
                                                        driver = 0;
                                                        break;
                                                }
                                                ct = 0;
                                        }
                                        ptrav = ptrav -> pnext;
                                }
                        }
                        if (flag == 1) {
                                break;
                        }
                        if (savecompress[i] == '\0') {
                                break;
                        }
                }
        } else {
                cout << "Decompressed file is not open" << endl;
        }
        decompressed_file.close();
        cout << endl;
        cout << "________________________________" << endl;
}

int main() {
        cList L, L2;
        cList2 L_Encode;
        cbstree tree;
        cnode * pnn, * ptrav;

        char letter[10000], savecompress[10000];
        int save_ct, check_zero = 1;

        reading(L, letter);
        cout << "________________________________" << endl;
        cout<<endl;
        cout << "The linked list" << endl;
        cout << "________________________________" << endl;
        cout<<endl;
        L.dispall();
        cout << "________________________________" << endl;
        arrange_isolate(L);
        cout << "The linked list sorted" << endl;
        cout << "________________________________" << endl;
        L.dispall();
        cout << "________________________________" << endl;
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
        combine(L, tree);
        cout<<endl;
        cout << "The linked list merged" << endl;
        cout << "________________________________" << endl;
        ptrav = L.phead;
        cout << "(" << ptrav -> x << ", " << ptrav -> info << ")" << ' ';
        cout << endl;
        //tree.dispall();
        cout<<endl;
        cout << "________________________________" << endl;
        int ct = 0, driver = 0, flag = 0;
        ptrav = L2.phead;
        cnode2 * pnn2;
        ctnode * pb = L.phead -> raddress;
        while (ptrav) {
                ct = 0, driver = 0, flag = 0;
                pnn2 = new cnode2;
                pb = L.phead -> raddress;
                count_BT(L.phead -> raddress, pb, pnn2, ptrav -> x[0], ct);
                pnn2 -> x = ptrav -> x[0];
                pb = L.phead -> raddress;
                traverse_BT(L.phead -> raddress, L.phead -> raddress, pb, pnn2, ptrav -> x[0], 0, driver, flag);
                pnn2 -> pnext = NULL;
                L_Encode.attach(pnn2);
                ptrav = ptrav -> pnext;
        }
        cout<<endl;
        cout << "Letters with code" << endl;
        cout << "________________________________" << endl;
        L_Encode.dispall();
        cout << "________________________________" << endl;

        // phase II 

        Compress(L_Encode, letter, savecompress, save_ct, check_zero);
        Decompress(L_Encode, savecompress, save_ct, check_zero);
        cout << "________________________________" << endl;
        cout << "Original text" << endl;
        cout << "________________________________" << endl;
        cout << letter << endl;
        cout << "________________________________" << endl;

        return 0;
}