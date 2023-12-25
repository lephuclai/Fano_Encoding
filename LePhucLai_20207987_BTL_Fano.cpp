#include<iostream>
#include<string>
#include<iomanip>
#include<time.h>
#include<cstdlib>


using namespace std;

bool check_int(string str) {
    for(int i = 0; i < str.length(); i++) {
        if(str[i] < '0' || str[i] > '9'){
            return false;
        }
    }
    return true;
}

struct node {
    string sym;
    float pro;
    int *arr = new int[20];
    int top;
};

void fano(int l, int h, node p[]) {
    float sum1 = 0, sum2 = 0, diff1 = 0, diff2 = 0;
    int k;
    if((l + 1) == h || l == h || l > h) {
        if(l == h || l > h) {
            return;
        }
        p[l].arr[++p[l].top] = 0;
        p[h].arr[++p[h].top] = 1;
        return;
    }
    else {
        for(int i = 1; i != h - l + 1; i++) {
            k = h - i;
            sum1 = sum2 = 0;
            for(int j = l; j <= k; j++) {
                sum1 += p[j].pro;
            }
            for(int j = h; j > k; j--) {
                sum2 += p[j].pro;
            }
            if(i == 1) {
                diff1 = sum1 - sum2;
                if(diff1 < 0) {
                    diff1 = diff1 * (-1);
                }
                continue;
            }
            diff2 = sum1 - sum2;
            if(diff2 < 0) {
                diff2 = diff2 * (-1);
            }
            if(diff2 >= diff1) {
                k++;
                break;
            }
            diff1 = diff2;
        } 
        for(int i = l; i <= k; i++) {
            p[i].arr[++(p[i].top)] = 0;
        }
        for(int i = k + 1; i <= h; i++) {
            p[i].arr[++(p[i].top)] = 1;
        }
        fano(l, k, p);
		fano(k + 1, h, p);
    }
}

void sortByPro(int n, node p[]) {
    node temp;
    for(int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if(p[j].pro > p[i].pro) {
                temp.pro = p[i].pro;
                temp.sym = p[i].sym;
                
                p[i].pro = p[j].pro;
                p[i].sym = p[j].sym;

                p[j].pro = temp.pro;
                p[j].sym = temp.sym;
            }   
        }
    }
}

void print(int n, node p[]) {
    cout << setfill(' ') << left << setw(20) << "Ky hieu" 
    << setfill(' ') << left << setw(20) << "Xac suat"
    << setfill(' ') << left << setw(10) << "Tu ma" << endl;
    for(int i = 0; i < n; i++) {
        cout << setfill(' ') << left << setw(20) << p[i].sym
        << setfill(' ') << left << setw(20) << p[i].pro;
        for(int j = 0; j <= p[i].top; j++) {
            cout << p[i].arr[j];
        }
        cout << endl;
    }

}

int main() {    
    int option;
    cout << "Chon che do nhap du lieu: " << endl;
    cout << "1. Che do tu dong" << endl;
    cout << "2. Che do thu cong" << endl;
    cout << "Lua chon: ";
    while (true) {
        cin >> option;
        if (option != 2 && option != 1) {
            cout << "Nhap lai lua chon: ";
        }
        else {
            break;
        }
    }

    if(option == 1){
        srand(time(0));
        float total = 0;
        int m;
        m = rand() % 10 + 1;
        int *num = new int[m];
        int sum = 0;
        for(int i = 0; i < m; i++) {
            num[i] = rand();
            sum += num[i];
        }
        node *p = new node[m];
        for(int i = 0; i < m; i++) {
            p[i].pro = float(num[i]) / float(sum);
            string pre = "x";
            string post = to_string(i);
            p[i].sym = pre.append(post);
        }
        sortByPro(m, p);
        for (int i = 0; i < m; i++) {
            p[i].top = -1;
        }
        fano(0, m - 1, p);
        print(m, p);
    }
        
    if(option == 2) {
        float total;
        int m;
        cout << "Nhap so ky tu: ";
        string insert;
        cin >> insert;
        while(true) {
            if(check_int(insert) == false) {
                cout << "Nhap lai so ky tu: ";
                cin >> insert;
                continue;
            }
            else {
                m = stoi(insert);
                break;
            }
        }

        node *p = new node[m];

        for (int i = 0; i < m; i++) {
		    cout << "Nhap ky tu thu " << i + 1 << ": ";
		    cin >> p[i].sym;
	    }

	    for (int i = 0; i < m; i++) {
		    cout << "Nhap xac suat cua " << p[i].sym << ": ";
            while(true) {
                cin >> p[i].pro;
                if(p[i].pro < 0) {
                    cout << "Xac suat khong hop le. Nhap lai: ";
                }
                else {
                    break;
                }
            }
		
		    total = total + p[i].pro;

            if (total > 1) {
                cout << "Khong hop le" << endl;
                total = total - p[i].pro;
                i--;
            }
        }
        sortByPro(m, p);
        for (int i = 0; i < m; i++) {
            p[i].top = -1;
        }

        fano(0, m - 1, p);
        print(m, p);
    }
    return 0;
}