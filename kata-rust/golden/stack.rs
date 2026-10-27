struct Node<T> {
    value: T,
    prev: Option<Box<Node<T>>>,
}

pub struct Stack<T> {
    head: Option<Box<Node<T>>>,
    len: usize,
}

impl<T> Default for Stack<T> {
    fn default() -> Self {
        Self { head: None, len: 0 }
    }
}

impl<T: Clone> Stack<T> {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn push(&mut self, item: T) {
        let prev = self.head.take();
        self.head = Some(Box::new(Node { value: item, prev }));
        self.len += 1;
    }

    pub fn pop(&mut self) -> Option<T> {
        let node = self.head.take()?;
        self.head = node.prev;
        self.len -= 1;
        Some(node.value)
    }

    pub fn peek(&self) -> Option<T> {
        self.head.as_ref().map(|n| n.value.clone())
    }

    pub fn len(&self) -> usize {
        self.len
    }

    pub fn is_empty(&self) -> bool {
        self.len() == 0
    }
}
