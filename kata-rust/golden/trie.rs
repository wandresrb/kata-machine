use std::collections::BTreeMap;

#[derive(Default)]
struct Node {
    children: BTreeMap<char, Node>,
    is_word: bool,
}

#[derive(Default)]
pub struct Trie {
    root: Node,
}

impl Trie {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn insert(&mut self, item: &str) {
        let mut node = &mut self.root;
        for c in item.chars() {
            node = node.children.entry(c).or_default();
        }
        node.is_word = true;
    }

    pub fn find(&self, partial: &str) -> Vec<String> {
        let mut node = &self.root;
        for c in partial.chars() {
            match node.children.get(&c) {
                Some(next) => node = next,
                None => return Vec::new(),
            }
        }
        let mut out = Vec::new();
        let mut prefix = partial.to_string();
        Self::collect(node, &mut prefix, &mut out);
        out
    }

    pub fn delete(&mut self, item: &str) {
        let chars: Vec<char> = item.chars().collect();
        Self::delete_rec(&mut self.root, &chars);
    }

    fn collect(node: &Node, prefix: &mut String, out: &mut Vec<String>) {
        if node.is_word {
            out.push(prefix.clone());
        }
        for (&c, child) in &node.children {
            prefix.push(c);
            Self::collect(child, prefix, out);
            prefix.pop();
        }
    }

    /// Unmarks the word and prunes nodes that no longer lead anywhere.
    /// Returns whether `node` itself can now be removed by its parent.
    fn delete_rec(node: &mut Node, rest: &[char]) -> bool {
        match rest.split_first() {
            None => node.is_word = false,
            Some((c, tail)) => {
                if let Some(child) = node.children.get_mut(c)
                    && Self::delete_rec(child, tail)
                {
                    node.children.remove(c);
                }
            }
        }
        !node.is_word && node.children.is_empty()
    }
}
