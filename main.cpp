#include <iostream>
#include <string>
#include <curl/curl.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response) {
    size_t totalSize = size * nmemb;
    response->append((char *) contents, totalSize);
    return totalSize;
}

int main() {
    // ChatGPT 的 API 端点
    std::string apiEndpoint = "https://api.openai.com//v1/chat/completions";

    // ChatGPT 的访问令牌（API 密钥）
    std::string apiKey = "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";

    // 输入的对话历史

    std::string conversation = R"({
    "model": "davinci",
    "messages": [{"role": "system", "content": "You are a helpful assistant."}, {"role": "user", "content": "Hello!"}]
})";


    // 初始化 libcurl
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    if (curl) {
        // 设置代理服务器地址和端口
        curl_easy_setopt(curl, CURLOPT_PROXY, "192.168.2.5");
        curl_easy_setopt(curl, CURLOPT_PROXYPORT, 10001);

        // 设置要请求的 URL
        curl_easy_setopt(curl, CURLOPT_URL, apiEndpoint.c_str());

        // 设置 POST 请求
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, conversation.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, conversation.length());

        // 设置请求头部
        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // 设置响应回调函数
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // 发送 HTTP 请求
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // 输出响应
            std::cout << response << std::endl;
        }

        // 清理 curl 相关资源
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "curl_easy_init() failed." << std::endl;
    }

    // 清理全局 curl 资源
    curl_global_cleanup();

    return 0;
}
