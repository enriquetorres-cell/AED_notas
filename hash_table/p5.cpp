#include <bits/stdc++.h>
using namespace std;

const long long OFFSET = 2e9;

template<typename key_type, typename value_type>
struct my_map {
    int m;
    int _size;
    vector<vector<pair<key_type, value_type>>> chains;

    my_map(int m = 1) : m(m), _size(0) { chains.resize(m); }

    int _hash(long long key) const {
        const int B = 311, MOD = 1e9 + 7;
        key += OFFSET;
        int hash_value = 0;
        while (key > 0) {
            int d = key % 10;
            hash_value = (1ll * hash_value * B + (d + 1)) % MOD;
            key /= 10;
        }
        return hash_value % m;
    }

    int _hash(const string &key) const {
        const int B = 311, MOD = 1e9 + 7;
        int hash_value = 0;
        for (unsigned char c : key) {
            hash_value = (1ll * hash_value * B + (c + 1)) % MOD;
        }
        return hash_value % m;
    }

    value_type& operator [] (const key_type &key) {
        int cp = _hash(key);
        int at = 0;
        while (at < (int)chains[cp].size() and chains[cp][at].first != key) ++at;
        if (at == (int)chains[cp].size()) {
            chains[cp].emplace_back(key, value_type());
            ++_size;
        }
        return chains[cp][at].second;
    }

    bool has_key(const key_type &key) const {
        int cp = _hash(key);
        int at = 0;
        while (at < (int)chains[cp].size() and chains[cp][at].first != key) ++at;
        return at != (int)chains[cp].size();
    }

    void erase(const key_type &key) {
        int cp = _hash(key);
        int at = 0;
        while (at < (int)chains[cp].size() and chains[cp][at].first != key) ++at;
        if (at != (int)chains[cp].size()) {
            if (at + 1 < (int)chains[cp].size()) swap(chains[cp][at], chains[cp].back());
            chains[cp].pop_back();
            --_size;
        }
    }

    void erase_all(const value_type &value) {
        for (int cp = 0; cp < m; ++cp) {
            int at = 0;
            while (at < (int)chains[cp].size()) {
                if (chains[cp][at].second == value) {
                    if (at + 1 < (int)chains[cp].size()) {
                        swap(chains[cp][at], chains[cp].back());
                    }
                    chains[cp].pop_back();
                    --_size;
                } else {
                    ++at;
                }
            }
        }
    }

    int  size()  const { return _size; }
    bool empty() const { return _size == 0; }

    void print() const {
        for (int i = 0; i < m; ++i) {
            cout << "Bucket " << i << ":\n";
            for (auto &e : chains[i]) cout << "  " << e.first << " --> " << e.second << '\n';
            cout << "End bucket\n";
        }
    }
};
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> grupos;
        my_map<string,int> gokussj1(2*strs.size());
        for(int i = 0; i < strs.size(); i++){
            string firma = strs[i];
            sort(firma.begin(),firma.end());
            if(!gokussj1.has_key(firma)){
                grupos.push_back({});
                gokussj1[firma] = grupos.size()-1;

            }
            grupos[gokussj1[firma]].push_back(strs[i]);
        }
        return grupos;
    }
};