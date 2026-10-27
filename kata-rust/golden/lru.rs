use std::collections::HashMap;
use std::hash::Hash;

/// A node in the recency list; lives in `Lru::nodes` and links by index.
struct Node<K, V> {
    key: K,
    value: V,
    prev: Option<usize>,
    next: Option<usize>,
}

/// LRU cache: a `HashMap` from key to slot plus an index-based doubly linked
/// list (head = most recently used, tail = eviction candidate). All ops O(1).
pub struct Lru<K, V> {
    capacity: usize,
    lookup: HashMap<K, usize>,
    nodes: Vec<Node<K, V>>,
    head: Option<usize>,
    tail: Option<usize>,
}

impl<K: Hash + Eq + Clone, V: Clone> Lru<K, V> {
    pub fn new(capacity: usize) -> Self {
        Self {
            capacity,
            lookup: HashMap::with_capacity(capacity),
            nodes: Vec::with_capacity(capacity),
            head: None,
            tail: None,
        }
    }

    pub fn update(&mut self, key: K, value: V) {
        if let Some(&idx) = self.lookup.get(&key) {
            self.nodes[idx].value = value;
            self.detach(idx);
            self.push_front(idx);
            return;
        }
        if self.capacity == 0 {
            return;
        }

        let idx = if self.nodes.len() < self.capacity {
            self.nodes.push(Node {
                key: key.clone(),
                value,
                prev: None,
                next: None,
            });
            self.nodes.len() - 1
        } else {
            // Reuse the least recently used slot.
            let idx = self.tail.expect("full cache has a tail");
            self.detach(idx);
            let old = std::mem::replace(
                &mut self.nodes[idx],
                Node {
                    key: key.clone(),
                    value,
                    prev: None,
                    next: None,
                },
            );
            self.lookup.remove(&old.key);
            idx
        };
        self.lookup.insert(key, idx);
        self.push_front(idx);
    }

    pub fn get(&mut self, key: &K) -> Option<V> {
        let idx = *self.lookup.get(key)?;
        self.detach(idx);
        self.push_front(idx);
        Some(self.nodes[idx].value.clone())
    }

    fn detach(&mut self, idx: usize) {
        let (prev, next) = (self.nodes[idx].prev, self.nodes[idx].next);
        match prev {
            Some(p) => self.nodes[p].next = next,
            None => self.head = next,
        }
        match next {
            Some(n) => self.nodes[n].prev = prev,
            None => self.tail = prev,
        }
        self.nodes[idx].prev = None;
        self.nodes[idx].next = None;
    }

    fn push_front(&mut self, idx: usize) {
        self.nodes[idx].next = self.head;
        if let Some(h) = self.head {
            self.nodes[h].prev = Some(idx);
        }
        self.head = Some(idx);
        if self.tail.is_none() {
            self.tail = Some(idx);
        }
    }
}
