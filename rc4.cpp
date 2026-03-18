#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int N = 10;
    vector<int> S = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> K = {2, 4, 1, 7};
    
    // Lập lịch khóa (KSA)
    int j_ksa = 0;
    for (int i = 0; i < N; i++) {
        j_ksa = (j_ksa + S[i] + K[i % K.size()]) % N;
        swap(S[i], S[j_ksa]);
    }
    
    cout << "IS = ";
    for (int x : S) cout << x << " ";
    cout << "\n\n";
    
    // Sinh dòng khóa và mã hóa (PRGA)
    string plaintext = "cybersecurity";
    string ciphertext = "";
    
    int i = 0;
    int j = 0;
    int step = 1;
    
    for (char c : plaintext) {
        int old_i = i;
        int old_j = j;
        
        cout << "Step " << step << " (Ky tu '" << c << "'): \n";
        
        // Tính i
        i = (i + 1) % N;
        cout << "    i = (" << old_i << " + 1) mod " << N << " = " << i << "\n";
        
        // Lấy giá trị S[i] trước khi hoán vị để in công thức
        int s_i_val = S[i];
        
        // Tính j
        j = (j + S[i]) % N;
        cout << "    j = (" << old_j << " + S[" << i << "]) mod " << N 
             << " = (" << old_j << " + " << s_i_val << ") mod " << N << " = " << j << "\n";
             
        cout << "    Swap(S[" << i << "], S[" << j << "])\n";
        
        // Thực hiện hoán vị
        swap(S[i], S[j]);
        
        // In mảng S
        cout << "    -> S = ";
        for (int x : S) cout << x << " ";
        cout << "\n";
        
        // Lấy giá trị S[i] và S[j] sau khi hoán vị để tính t
        int s_i_after = S[i];
        int s_j_after = S[j];
        
        // Tính t theo công thức
        int t = (S[i] + S[j]) % N;
        cout << "    t = (S[" << i << "] + S[" << j << "]) mod " << N 
             << " = (" << s_i_after << " + " << s_j_after << ") mod " << N << " = " << t << "\n";
             
        // Lấy dòng khóa k
        int k = S[t];
        cout << "    -> k_" << step << " = S[" << t << "] = " << k << "\n";
        
        // Tính bản mã (XOR)
        int m = (int)c;
        int cipher_byte = m ^ k;
        char cipher_char = (char)cipher_byte;
        ciphertext += cipher_char;
        
        cout << "    [" << c << " = " << m << " -> " << m << " XOR " << k 
             << " = " << cipher_byte << " -> " << cipher_char << "]\n";
        cout << "--------------------------------------------------\n";
        
        step++;
    }
    
    // In kết quả cuối
    cout << "\n=> C(t) = \"";
    for (int i = 0; i < ciphertext.length(); i++) {
        cout << ciphertext[i];
        if (i < ciphertext.length() - 1) cout << " ";
    }
    cout << "\"\n";

    return 0;
}