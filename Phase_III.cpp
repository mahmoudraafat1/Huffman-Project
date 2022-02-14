#include <iostream>

#include <fstream>

#include <string>

#include <stdio.h>

using namespace std;

class ctnode {
        public:
                char * x;
        int info;
        int index = 0;
        ctnode * pleft;
        ctnode * pright;
};
class cnode {
        public:
                char * x;
        int info = 1;
        int index = 0;
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
                        cout << "(";
                        for (int i = 0; i < ptrav -> index; i++) {
                                cout << ptrav -> x[i];
                        }
                        cout << ", " << ptrav -> info << ")" << ' ';
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
                        cout << ")" << endl;
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
                for (int i = 0; i < pt -> index; i++) {
                        cout << pt -> x[i] << endl;
                }
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

void reading(cList & L, char * & letter, int & ct) {
        char * check = NULL;
        int flag = 0, check_tool = 0, check_help = 0;
        cnode * pnn;
        ifstream xfile;
        ifstream fl("/home/mahmoud-raafat/Downloads/sample.bmp", ifstream::binary);
        fl.seekg(0, fl.end);
        ct = fl.tellg();
        fl.seekg(0, fl.beg);
        char ch;
        letter = new char[ct];
        check = new char[ct];
        for (int i = 0; i < ct; i++) {
                fl.read( & ch, 1);
                letter[i] = ch;
        }
        cout << endl;
        xfile.close();
        for (int i = 0; i < ct; i++) {
                for (int k = i + 1, check_help = 0; check_help < check_tool; k++, check_help++) {
                        if (letter[i] == check[check_help]) {
                                flag = 1;
                                break;
                        }
                }
                check[check_tool] = letter[i], check_tool++;
                if (flag == 0) {
                        pnn = new cnode;
                        pnn -> x = new char[ct];
                        pnn -> x[0] = letter[i], pnn -> index = 1;
                        pnn -> pnext = NULL, pnn -> raddress = NULL;
                        for (int k = i + 1; k < ct; k++) {
                                if (letter[i] == letter[k]) pnn -> info++;
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
                if (ptrav -> pnext == NULL) L.ptail = ptrav;
                
                ptrav = ptrav -> pnext;
        }
}
void combine(cList & L, cbstree & tree, int ct) {
        ctnode * pnnt;
        cnode * pnn, * ptrav1 = L.phead, * ptrav2 = ptrav1 -> pnext, * ptemp = L.phead;
        int comb = 0, flag = 0;
        while (ptemp != NULL) {
                comb = 0, flag = 0;
                pnn = new cnode;
                pnnt = new ctnode;
                pnn -> x = new char[ct];
                pnnt -> x = new char[ct];
                for (int i = 0; i < ptrav1 -> index; i++, comb++) {
                        pnnt -> x[comb] = ptrav1 -> x[i];
                        pnn -> x[comb] = ptrav1 -> x[i];
                }
                for (int k = 0; k < ptrav2 -> index; k++, comb++) {
                        pnnt -> x[comb] = ptrav2 -> x[k];
                        pnn -> x[comb] = ptrav2 -> x[k];
                }
                pnn -> index = ptrav1 -> index + ptrav2 -> index;
                pnnt -> index = ptrav1 -> index + ptrav2 -> index;
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
                        pnnt -> x = new char[ct];
                        for (int i = 0; i < ptrav1 -> index; i++) pnnt -> x[i] = ptrav1 -> x[i];
                        
                        pnnt -> index = ptrav1 -> index;
                        pnnt -> info = ptrav1 -> info;
                        pnnt -> pleft = NULL, pnnt -> pright = NULL;
                        tree.insert(pnnt);
                        pnnt = new ctnode;
                        pnnt -> x = new char[ct];
                        for (int i = 0; i < ptrav2 -> index; i++) pnnt -> x[i] = ptrav2 -> x[i];
                        
                        pnnt -> index = ptrav2 -> index;
                        pnnt -> info = ptrav2 -> info;
                        pnnt -> pleft = NULL, pnnt -> pright = NULL;
                        tree.insert(pnnt);
                        flag = 1;
                }
                if (ptrav1 -> raddress == NULL && ptrav2 -> raddress != NULL && flag == 0) {
                        tree.proot -> pright = ptrav2 -> raddress;
                        pnnt = new ctnode;
                        pnnt -> x = new char[ct];
                        for (int i = 0; i < ptrav1 -> index; i++) pnnt -> x[i] = ptrav1 -> x[i];

                        pnnt -> index = ptrav1 -> index;
                        pnnt -> info = ptrav1 -> info;
                        pnnt -> pleft = NULL, pnnt -> pright = NULL;
                        tree.insert(pnnt);
                        flag = 1;
                }
                if (ptrav1 -> raddress != NULL && ptrav2 -> raddress == NULL && flag == 0) {
                        tree.proot -> pleft = ptrav1 -> raddress;
                        pnnt = new ctnode;
                        pnnt -> x = new char[ct];
                        for (int i = 0; i < ptrav2 -> index; i++) pnnt -> x[i] = ptrav2 -> x[i];
                
                        pnnt -> index = ptrav2 -> index;
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
                if (pb != NULL && pb -> x[0] == y && pb -> index == 1) {
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
void traverse_BT(ctnode * proot, ctnode * pt, ctnode * & pb, cnode2 * & pnn, char y, int number, int comb, int & flag) {
        if (pt == NULL) {
                if (pb != NULL && pb -> x[0] == y && pb -> index == 1 && flag == 0) flag = 1;

                return;
        }
        if (pt != NULL) pb = pt;
        
        if (flag == 0 && pt != proot && comb < pnn -> size) {
                pnn -> info[comb] = number;
                comb++;
        }
        traverse_BT(proot, pt -> pleft, pb, pnn, y, 0, comb, flag);
        traverse_BT(proot, pt -> pright, pb, pnn, y, 1, comb, flag);
}

void Compress(cList2 & L_Encode, char * & letter, char * & savecompress, int & save_count, int & check_zero, int ct, int & ct3) {
        cnode2 * ptrav = L_Encode.phead;
        char x = 0, m = 1;
        int ct2 = 0, comb = 0;
        int binary[8];
        ofstream compressed_file("/home/mahmoud-raafat/Downloads/sample.bmp", ofstream::binary);
        cout<<endl;
        cout << "Compressed text" << endl;
        cout << "__________________"<< endl;
        cout<<endl;
        for (int i = 0; i < ct; i++) {
                ptrav = L_Encode.phead;
                while (ptrav != NULL) {
                        if (letter[i] == ptrav -> x) {
                                for (int k = 0; k < ptrav -> size; k++) {
                                        if (ptrav -> info[k] == 1) x = x | (m << ct2);
                                        ct2++;
                                        if (ct2 == 8) {
                                                ct2 = 0;
                                                cout << x;
                                                savecompress[comb] = x;
                                                comb++;
                                                ct3++;
                                                compressed_file.write( & x, 1);
                                                x = 0;
                                        }
                                }
                        }
                        ptrav = ptrav -> pnext;
                }
        }
        if (ct2 > 0) {
                savecompress[comb] = x;
                ct3++;
                cout << x;
                compressed_file.write( & x, 1);
                save_count = ct2;
                if (x == 0 && ct2 > 0) check_zero = 0;
        }
        compressed_file.close();
        cout << endl;
        cout << "______________________________________________________________________"<< endl;
}
void Decompress(cList2 & L_Encode, char * & savecompress, int & save_count, int & check_zero, int ct2, int ct3) {
        ifstream compressed_file("/home/mahmoud-raafat/Downloads/sample.bmp", ofstream::binary);
        ofstream decompressed_file("/home/mahmoud-raafat/Downloads/sample.bmp", ofstream::binary);;
        cnode2 * ptrav = L_Encode.phead;
        char * compressed_letter;
        char m = 1, res;
        int ct = 0, shift = 0, comb = 0, range = 8, flag = 0;
        int * binary;
        binary = new int[ct2];
        compressed_letter = new char[ct2];
      
        compressed_file.close();
        cout << "_________________________"<< endl;
        cout<<endl;
        cout << "Copied compressed text" << endl;
        cout << "_________________________"<< endl;
        cout<<endl;
        cout << savecompress << endl;
        cout << "__________________________________________________"<< endl;
        cout<<endl;
        cout << "Decompressed text" << endl;
        cout << "___________________"<< endl;
        cout<<endl;
        cout << "Decompressed file is open" << endl;
        cout << "____________________________"<< endl;
        cout<<endl;
        for (int i = 0 ;  ;i++) {
                if (check_zero == 1 && i == ct3) break;
                if (check_zero == 0 && i == ct3 && save_count > 0) {
                        range = save_count;
                        flag = 1;
                } else {
                        if (check_zero == 1 && i + 1 == ct3 && save_count > 0) {
                                range = save_count;
                                flag = 1;
                        }
                }
                for (int j = 0; j < range; j++) {
                        res = savecompress[i] & (m << shift);
                        shift++;
                        if (res != 0) {
                                binary[comb] = 1;
                                comb++;
                        } else {
                                binary[comb] = 0;
                                comb++;
                        }
                        if (shift == 8) shift = 0;
                        res = 0;
                        ptrav = L_Encode.phead;
                        while (ptrav != NULL) {
                                if (comb == ptrav -> size) {
                                        for (int k = 0; k < ptrav -> size; k++) {
                                                if (ptrav -> info[k] == binary[k]) ct++;
                                                else ct = 0;
                                                
                                        }
                                        if (ptrav -> size == ct) {
                                                ct = 0;
                                                cout << ptrav -> x;
                                                decompressed_file.write( & ptrav -> x, 1);
                                                comb = 0;
                                                break;
                                        }
                                        ct = 0;
                                }
                                ptrav = ptrav -> pnext;
                        }
                }
                if (flag == 1) break;
                if (i == ct3) break;
                
        }
        decompressed_file.close();
        cout << endl;
        cout << "_______________________________________________________________________"<< endl;
}

int main() {
        cList L, L2;
        cList2 L_Encode;
        cbstree tree;
        cnode * pnn, * ptrav;

        char * letter = NULL;
        int save_count, check_zero = 1, ct = 0;

        reading(L, letter, ct);
        arrange_isolate(L);
        cout << "________________________"<< endl;
        cout<<endl;
        cout << "The linked list sorted" << endl;
        cout << "________________________"<< endl;
        cout<<endl;
        L.dispall();
        cout << "___________________________________________________________________________"<< endl;
        ptrav = L.phead;
        while (ptrav != NULL) {
                pnn = new cnode;
                pnn -> x = new char[ct];
                pnn -> x[0] = ptrav -> x[0];
                pnn -> index = 0;
                pnn -> info = ptrav -> info;
                pnn -> pnext = NULL, pnn -> pnext = NULL;
                L2.attach(pnn);
                ptrav = ptrav -> pnext;
        }
        combine(L, tree, ct);
        cout << "________________________"<< endl;
        cout<<endl;
        cout << "The linked list merged" << endl;
        cout << "________________________"<< endl;
        cout<<endl;
        ptrav = L.phead;
        cout << "(" << ptrav -> x << ", " << ptrav -> info << ")" << ' ';
        cout << endl;
        //tree.dispall();
        cout << "__________________________________________________________________"<< endl;
        int ct2 = 0, comb = 0, flag = 0;
        ptrav = L2.phead;
        cnode2 * pnn2;
        ctnode * pb = L.phead -> raddress;
        while (ptrav != NULL) {
                ct2 = 0, comb = 0, flag = 0;
                pnn2 = new cnode2;
                pb = L.phead -> raddress;
                count_BT(L.phead -> raddress, pb, pnn2, ptrav -> x[0], ct2);
                pnn2 -> x = ptrav -> x[0];
                pb = L.phead -> raddress;
                traverse_BT(L.phead -> raddress, L.phead -> raddress, pb, pnn2, ptrav -> x[0], 0, comb, flag);
                pnn2 -> pnext = NULL;
                L_Encode.attach(pnn2);
                ptrav = ptrav -> pnext;
        }
        cout << "____________________"<< endl;
        cout<<endl;
        cout << "Letters with code" << endl;
        cout << "____________________"<< endl;
        cout<<endl;
        L_Encode.dispall();
        cout << "_________________________________________________________________________"<< endl;

        //phase II
        char * savecompress;
        int ct3 = 0;
        savecompress = new char[ct];
        Compress(L_Encode, letter, savecompress, save_count, check_zero, ct, ct3);
        Decompress(L_Encode, savecompress, save_count, check_zero, ct, ct3);
        cout<<endl;
        cout<<"no. of noncompressed bytes: 710 "<<endl;
        cout <<"no. of compressed bytes: "<< ct3 << endl;
        cout << "__________________________________________________________________________"<< endl;

        return 0;
}