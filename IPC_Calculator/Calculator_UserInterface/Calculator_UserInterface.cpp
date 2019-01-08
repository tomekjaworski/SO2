// Calculator_UserInterface.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <assert.h>
#include <windows.h>

volatile struct ipc_data_t
{
	float val1, val2, result;
	char op;

	bool success;
	char error_message[1024];
};

int main()
{
	// FAZA 1. Przygotuj zasoby wykorzystywne w komunikacji IPC
	// Wszystkie elementy muszą być gotowe zanim utworzony zostanie semafor "sem_i_am_ready".
	// Dzięki temu unikniemy nieporządku w kodzie, gdzie jeden proces tworzy cześć zasobów współ dzielonych
	// a chwilę później drugi robi to samo.

	// przygotuj semafory do przepływu sterowania wykonywaniem obu programów
	HANDLE sem_execute = CreateSemaphore(NULL, 0, 1, "sem_execute");
	assert(sem_execute != nullptr); // uproszczona kontrola błędów

	HANDLE sem_results = CreateSemaphore(NULL, 0, 1, "sem_results");
	assert(sem_results != nullptr); // uproszczona kontrola błędów

	// przygotuj blok wspólnej pamięci
	// - plik mapowany
	HANDLE file_map_handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL,
		PAGE_READWRITE, 0, sizeof(ipc_data_t), "so1_calc_data");

	if (file_map_handle == nullptr)
	{
		// przydatne, bo można zobaczyć kod błędu
		printf("A to peszek (%d)\n", GetLastError());
		CloseHandle(sem_execute);
		CloseHandle(sem_results);
		exit(-1);
	}

	// mapuj fragment pliku
	ipc_data_t *pdata = (ipc_data_t*)MapViewOfFile(file_map_handle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(ipc_data_t));
	if (pdata == nullptr)
	{
		printf("A to peszek (%d)\n", GetLastError());
		CloseHandle(file_map_handle);
		CloseHandle(sem_execute);
		CloseHandle(sem_results);
		exit(-1);
	}

	   
	// FAZA 2. Czekaj na proces liczący
	// Uwaga! Utworzenie tego semafora jest granicą rozdzielającą fazę przygotowania
	// zaobów współdzielonych i ich używania
	printf("Oczekiwanie na proces liczacy: ");
	HANDLE sem_waiter = CreateSemaphore(NULL, 0, 1, "sem_i_am_ready"); // domyślnie niesygnalizuący
	assert(sem_waiter != nullptr); // dla uproszczenia, choć powinien być if z CloseHandle

	while (true)
	{
		DWORD result = WaitForSingleObject(sem_waiter, 1000);
		if (result == WAIT_OBJECT_0)
			break;

		printf("."); // pokaż, że żyjesz...
	}

	printf("Ok!\n");
	CloseHandle(sem_waiter);

	while (true) {

		printf("Podaj liczbe A: ");
		int n1 = scanf("%f", &pdata->val1);

		printf("Podaj liczbe B: ");
		int n2 = scanf("%f", &pdata->val2);

		printf("Podaj operacje (+, -, /, * lub q zeby wyjsc): ");
		int n3 = scanf("%*c%c", &pdata->op);

		if (!n1 || !n2 || !n3)
		{
			printf("Blad danych wejsciowych; spodziewane dwie liczby oraz operator");
			UnmapViewOfFile(pdata);
			CloseHandle(file_map_handle);
			CloseHandle(sem_execute);
			CloseHandle(sem_results);
			exit(-1);
		}

		if (pdata->op == 'q') {
			// ok, legalnie kończymy proces
			UnmapViewOfFile(pdata);
			CloseHandle(file_map_handle);
			CloseHandle(sem_execute);
			CloseHandle(sem_results);
			exit(0);
		}


		// sygnalizuj start obliczeń
		ReleaseSemaphore(sem_execute, 1, NULL);

		// i tutaj dzieje się magia w drugim procesie, a my czekamy :)

		// czekaj na wyniki
		WaitForSingleObject(sem_results, INFINITE);


		if (pdata->success)
			printf("Wynik: %f %c %f = %f\n", pdata->val1, pdata->op, pdata->val2, pdata->result);
		else
			printf("Blad  %f %c %f = %s\n", pdata->val1, pdata->op, pdata->val2, pdata->error_message);

	}
}
