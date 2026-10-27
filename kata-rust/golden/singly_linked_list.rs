use crate::types::List;

struct Node<T> {
    value: T,
    next: Link<T>,
}

type Link<T> = Option<Box<Node<T>>>;

pub struct SinglyLinkedList<T> {
    head: Link<T>,
    len: usize,
}

impl<T> Default for SinglyLinkedList<T> {
    fn default() -> Self {
        Self { head: None, len: 0 }
    }
}

impl<T> SinglyLinkedList<T> {
    pub fn new() -> Self {
        Self::default()
    }

    /// Mutable reference to the link that points at node `idx` (`idx == len` is the tail link).
    fn link_at(&mut self, idx: usize) -> &mut Link<T> {
        let mut cur = &mut self.head;
        for _ in 0..idx {
            cur = &mut cur.as_mut().expect("index checked by caller").next;
        }
        cur
    }
}

impl<T: Clone + PartialEq> List<T> for SinglyLinkedList<T> {
    fn len(&self) -> usize {
        self.len
    }

    fn prepend(&mut self, item: T) {
        self.insert_at(item, 0);
    }

    fn append(&mut self, item: T) {
        self.insert_at(item, self.len);
    }

    fn insert_at(&mut self, item: T, idx: usize) {
        assert!(
            idx <= self.len,
            "insert_at index {idx} out of bounds (len {})",
            self.len
        );
        let link = self.link_at(idx);
        let next = link.take();
        *link = Some(Box::new(Node { value: item, next }));
        self.len += 1;
    }

    fn remove(&mut self, item: &T) -> Option<T> {
        let mut idx = 0;
        let mut cur = self.head.as_deref();
        while let Some(node) = cur {
            if node.value == *item {
                return self.remove_at(idx);
            }
            cur = node.next.as_deref();
            idx += 1;
        }
        None
    }

    fn get(&self, idx: usize) -> Option<T> {
        let mut cur = self.head.as_deref();
        for _ in 0..idx {
            cur = cur?.next.as_deref();
        }
        cur.map(|n| n.value.clone())
    }

    fn remove_at(&mut self, idx: usize) -> Option<T> {
        if idx >= self.len {
            return None;
        }
        let link = self.link_at(idx);
        let node = link.take()?;
        *link = node.next;
        self.len -= 1;
        Some(node.value)
    }
}

impl<T> Drop for SinglyLinkedList<T> {
    /// Iterative drop so long lists don't blow the stack with recursive Box drops.
    fn drop(&mut self) {
        let mut cur = self.head.take();
        while let Some(mut node) = cur {
            cur = node.next.take();
        }
    }
}
