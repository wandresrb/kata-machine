use kata::code::ring_buffer::RingBuffer;

#[test]
fn ring_buffer() {
    let mut buffer = RingBuffer::new();

    buffer.push(5);
    assert_eq!(buffer.pop(), Some(5));
    assert_eq!(buffer.pop(), None);

    buffer.push(42);
    buffer.push(9);
    assert_eq!(buffer.pop(), Some(42));
    assert_eq!(buffer.pop(), Some(9));
    assert_eq!(buffer.pop(), None);

    buffer.push(42);
    buffer.push(9);
    buffer.push(12);
    assert_eq!(buffer.get(2), Some(12));
    assert_eq!(buffer.get(1), Some(9));
    assert_eq!(buffer.get(0), Some(42));
}
