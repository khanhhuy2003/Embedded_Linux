# README

## 1. Vai trò và các tham số chính của `pthread_create()` và `pthread_join()`

- **`pthread_create()`**:  
  - Chức năng: Tạo ra một **thread con** chạy song song với main thread và thực hiện công việc được giao.  
  - Tham số chính:
    1. `pthread_t *thread` : con trỏ đến biến lưu ID của thread vừa tạo.
    2. `const pthread_attr_t *attr` : thuộc tính của thread (có thể là `NULL` để dùng mặc định).
    3. `void *(*start_routine)(void *)` : con trỏ đến hàm mà thread sẽ thực thi.
    4. `void *arg` : tham số truyền vào hàm thread.
    
- **`pthread_join()`**:  
  - Chức năng: Yêu cầu **main thread** hoặc một thread khác chờ cho thread con chạy xong, sau đó thu dọn và giải phóng tài nguyên.  
  - Tham số chính:
    1. `pthread_t thread` : ID của thread cần chờ.
    2. `void **retval` : con trỏ nhận giá trị trả về của thread khi kết thúc (có thể là `NULL` nếu không cần).

- **Khi nào một luồng kết thúc**:  
  - Khi nó thực hiện xong tất cả công việc trong hàm của chính nó và gọi `return` hoặc `pthread_exit()`.  
  - Hoặc nếu main thread kết thúc trước, toàn bộ tiến trình sẽ kết thúc, làm tất cả thread cũng kết thúc theo.

---

## 2. Tại sao cần sử dụng mutex trong bài toán đa luồng

- Trong bài toán này, biến toàn cục `count` được **truy cập bởi nhiều thread đồng thời**.  
- Mỗi thread đều thực hiện phép **tăng `count`**. Nếu không có cơ chế đồng bộ:
  - Khi một thread đang thực hiện phép cộng chưa hoàn thành, thread khác có thể xen vào truy cập cùng biến.  
  - Điều này dẫn đến thao tác cập nhật không trọn vẹn hoặc bị ghi đè.  
  - Kết quả cuối cùng có thể **không chính xác và không ổn định**. Hiện tượng này được gọi là **race condition**.

- **Khi sử dụng mutex**:
  - Các đoạn code nằm giữa `pthread_mutex_lock()` và `pthread_mutex_unlock()` trở thành **critical section**.  
  - Điều này đảm bảo **tại một thời điểm chỉ có duy nhất một thread** được phép truy cập và thao tác trên tài nguyên dùng chung.  
  - Các thread khác phải chờ cho đến khi thread hiện tại giải phóng mutex, ngăn ngừa race condition.

---
