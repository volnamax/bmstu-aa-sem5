void run_pipeline(const std::vector<std::string> &filenames, const std::vector<std::string> &filenames_out, int count_f,
                  AtomicQueue<Request> &completedRequests) {
        AtomicQueue<Request> queue1, queue2, queue3;

    std::thread genThread(generator, std::ref(queue1), std::ref(filenames), std::ref(filenames_out), count_f);
    std::thread t1(device1, std::ref(queue1), std::ref(queue2));
    std::thread t1_2(device1, std::ref(queue1), std::ref(queue2));
    std::thread t2(device2, std::ref(queue2), std::ref(queue3));
    std::thread t3(device3, std::ref(queue3), std::ref(completedRequests));
    genThread.join();
    t1.join();
    t1_2.join(); 
    t2.join();
    t3.join();
}