#ifndef __XMALLOC_H__
#define __XMALLOC_H__

/* Allocate space for typed object. */
#define xmalloc(_type) ((_type *)_xmalloc(sizeof(_type), __alignof__(_type)))

/* Allocate space for array of typed objects. */
#define xmalloc_array(_type, _num) ((_type *)_xmalloc_array(sizeof(_type), __alignof__(_type), _num))

#define DEFAULT_ALIGN (sizeof(unsigned long))
#define malloc(size) _xmalloc(size, DEFAULT_ALIGN)
#define free(ptr) xfree(ptr)
#define realloc(ptr, size) _realloc(ptr, size)

/* Free any of the above. */
extern void xfree(const void *);

/* Underlying functions */
extern void *_xmalloc(size_t size, size_t align);
extern void *_realloc(void *ptr, size_t size);

static inline void *_xmalloc_array(size_t size, size_t align, size_t num)
{
	/* Check for overflow. */
	if (size && num > UINT_MAX / size)
		return NULL;
 	return _xmalloc(size * num, align);
}

#endif /* __XMALLOC_H__ */
