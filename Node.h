class Node {
public: 
	char ch;
	int frequency;
	Node* left;
	Node* right;

	Node(char c, int f, Node* l = nullptr, Node* r = nullptr)
		: ch(c), frequency(f), left(l), right(r) {
	}
};