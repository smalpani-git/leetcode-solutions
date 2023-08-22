// A simple trie based problem. 
// Insert a word into the dictionary.
// Search if a word exists.
// The search is interesting because it takes a wild card
// character and therfore requires recursing along possible
// children node. 

// Time Complexity 
// Insertion O(n) with extra work to allocate a Trie node at times.
// Search O(n) without any wild card. 
// When there is 1 wilcard at kth position, then the complexity is:

// k + 26*(n-k-1)
// If there are two wild cards at position p,q, then it becomes,
// p-1 + 26*(q-p-1+ 26*(n-q-1))

// If all characters are wildcards, then this simply becomes : 26**n

// However the number of words in the dictionary also plays a role. If the
// dictionary is sparse, then one doesn't have to go down the recursion path
// when there is no child node at a specific position.

class WordDictionary {

private:
    const static size_t ALPHABET_SIZE = 26;
    struct TrieNode {
        struct TrieNode *children[ALPHABET_SIZE];
        bool endsHere;

        TrieNode() : endsHere(false) {
            for(int i = 0; i < ALPHABET_SIZE; ++i) {
                children[i] = 0;
            }
        }
    };

    struct TrieNode *root;
public:
    WordDictionary() {
        root = new TrieNode();
    }

    // Iterate down the trie, creating a childNode whenever required.
    void addWord(string word) {
        TrieNode *cur = root;
        for(auto ch : word) {
            int idx = ch - 'a';
            if(!cur->children[idx]) {
                cur->children[idx] = new TrieNode();
            }
            cur = cur->children[idx];
        }
        cur->endsHere = true;
    }

    bool searchHelp(string word, size_t wordIdx,TrieNode *trie) {
       // Recurse down the trie, along the child that matches when the
       // word[wordIdx], otherwise, recurse down all the children when
       // the word[wordIdx] is a wild card.
        auto ch = word[wordIdx];
        if(ch != '.') {
            // Not a wildcard, regular match.
            int idx = ch - 'a';
            TrieNode* cur = trie->children[idx];
            if(!cur) {
                return false;
            } else {
                if(wordIdx==word.size()-1) {
                    return cur->endsHere;
                } 
                return searchHelp(word,wordIdx+1,cur);
            }
        } else {
            // Wild card case. Recurse down all children. 
            // If there are no children then fall through to the
            // end without recursion and this would return false.
            for(auto cur : trie->children) {
                if(cur) {
                    if(wordIdx==word.size()-1) {
                        if(cur->endsHere) {
                            // This is the last character and there is a word
                            // that ends here. 
                            return true;
                        }
                    } else {
                        // This is not the last character continue our search 
                        // down.
                        if(searchHelp(word,wordIdx+1,cur)) {
                            return true;
                        }
                    }
                } 
            }
            return false;
        }
        // This is dead code that makes the compiler happy. 
        return false;
    }
    
    bool search(string word) {
        return searchHelp(word,0,root);
    } 
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
