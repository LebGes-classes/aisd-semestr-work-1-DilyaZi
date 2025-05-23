#include <iostream>      
#include <queue>          
#include <unordered_map>  
#include <string>        
#include "Node.h"         

using namespace std;

class HuffmanTree {
public:
    Node* root;           
    unordered_map<char, string> codes; 
    //конструктор
    HuffmanTree() : root(nullptr) {}

    //деструктор
    ~HuffmanTree() {
        deleteTree(root); //освобождаем память дерева
    }

    //кодирование символов строки
    void encodeChars(Node* node, string code, unordered_map<char, string>& huffmanCode) {
        if (!node) {
            return;
        }
        if (!node->left && !node->right) { 
            huffmanCode[node->ch] = code;
            return;
        }
        encodeChars(node->left, code + "0", huffmanCode);  
        encodeChars(node->right, code + "1", huffmanCode); 
    }

    //oчистка памяти дерева
    void deleteTree(Node* node) {
        if (!node) {
            return;
        }
        deleteTree(node->left); 
        deleteTree(node->right); 
        delete node;
    }


    //компаратор для приоритетной очереди
    struct comp {
        bool operator()(Node* l, Node* r) {
            return l->frequency > r->frequency;
        }
    };

    //пострпоение дерева Хаффмана
    void buildHuffmanTree(const string& text) {
        //считаем частоту символов
        unordered_map<char, int> frequency;
        for (char c : text) {
            frequency[c]++;
        }

        //создаем приоритетную очередь
        priority_queue<Node*, vector<Node*>, comp> pq;
        for (const auto& pair : frequency) {
            pq.push(new Node(pair.first, pair.second, nullptr, nullptr));
        }

        while (pq.size() > 1) {
            Node* left = pq.top();
            pq.pop();
            Node* right = pq.top();
            pq.pop();
            Node* newNode = new Node('$', left->frequency + right->frequency, left, right);
            pq.push(newNode);
        }
        root = pq.top();
        encodeChars(root, "", codes);

        //выводим коды Хаффмана
        cout << "Коды Хаффмана:\n" << endl;
        for (const auto& pair : codes) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

    //кодирование строки
    string encode(const string& text) {
        string encodedStr;
        for (char c : text) {
            encodedStr += codes[c];
        }
        return encodedStr;
    }

    //декодирование строки
    string decode(const string& str) {
        string decodedStr;
        Node* current = root;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == '0') {
                current = current->left;
            }
            else {
                current = current->right;
            }
            if (!current->left && !current->right) {
                decodedStr += current->ch;
                current = root;
            }
        }
        return decodedStr;
    }

    void print(const string& text) {
        cout << "\nИсходная строка:\n" << text << endl;
        string encodedStr = encode(text);
        cout << "\nEncoded string:\n" << encodedStr << endl;
        string decodedStr = decode(encodedStr);
        cout << "\nDecoded string:\n" << decodedStr << endl;
    }
};

int main() {
    string text = "Huffman coding is a data compression algorithm.";
    HuffmanTree tree;
    tree.buildHuffmanTree(text);
    tree.print(text);
    return 0;
}