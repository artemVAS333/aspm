#include "app/app.h"

// int main(int argc, char *argv[])
// {
// 	App app(argc, argv);
// 	app.run();
// 	return 0;
// }

#include <iostream>
#include <string>

// #include <cstdio>

#include <curl/curl.h>
#include "app/app.h"

using namespace std;

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) { return fwrite(ptr, size, nmemb, stream); }

// int main(int argc, char *argv[])
int main()
{
	// App app(argc, argv);
	// app.run();

	const char *url = "https://github.com/artemVAS333/test/archive/refs/tags/v0.0.1-hello.tar.gz";
	const char *outfilename = "bin/mytool-v0.0.1.tar.gz";

	CURL *curl = curl_easy_init();
	FILE *fp;

	if (curl)
	{
		fp = fopen(outfilename, "wb");
		if (!fp)
		{
			perror("File open failed");
			return 1;
		}

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

		CURLcode res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		else
		{
			printf("Downloaded successfully: %s\n", outfilename);
		}

		fclose(fp);
		curl_easy_cleanup(curl);
	}

	return 0;
}
