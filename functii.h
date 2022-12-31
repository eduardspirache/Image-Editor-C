#pragma once

typedef struct {
	int red, green, blue;
} colors;

void myswap(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

int maxval(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int minval(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

int myround(double b)
{
	int a = b;
	int c = a + 1;
	if ((b - a) < (c - b))
		return a;
	else
		return c;
}

void makeascii(int okascii, char *type, char **temptype)
{
	if (okascii) {
		if (!strcmp(type, "P6"))
			*temptype = "P3";
		else if (!strcmp(type, "P5"))
			*temptype = "P2";
		else
			*temptype = type;
	} else {
		if (!strcmp(type, "P3"))
			*temptype = "P6";
		else if (!strcmp(type, "P2"))
			*temptype = "P5";
		else
			*temptype = type;
	}
}

int **get_raster(int rows, int columns, FILE *file)
{
	int **a = (int **)calloc(rows, sizeof(int *));
	for (int i = 0; i < rows; i++) {
		a[i] = calloc(columns, sizeof(int *));
		for (int j = 0; j < columns; j++) {
			if (a[i] == NULL)
				free(a[j]);
			else
				fscanf(file, "%d", &a[i][j]);
		}
	}
	return a;
}

colors **getcolor(int rows, int columns, FILE *file)
{
	colors **a = (colors **)calloc(rows, sizeof(int *));
	for (int i = 0; i < rows; i++) {
		a[i] = calloc(columns, 3 * sizeof(int *));
		for (int j = 0; j < columns; j++)
			if (a[i] == NULL)
				free(a[i]);
			else
				fscanf(file, "%d%d%d", &a[i][j].red, &a[i][j].green,
					   &a[i][j].blue);
	}
	return a;
}

int **get_raster_binary(int rows, int columns, FILE *file)
{
	int **a = (int **)calloc(rows, sizeof(char *));
	for (int i = 0; i < rows; i++) {
		a[i] = calloc(columns, sizeof(char *));
		for (int j = 0; j < columns; j++) {
			if (a[i] == NULL)
				free(a[j]);
			else
				fread(&a[i][j], sizeof(char), 1, file);
		}
	}
	return a;
}

colors **getcolor_binary(int rows, int columns, FILE *file)
{
	colors **a = (colors **)calloc(rows, sizeof(char *));
	for (int i = 0; i < rows; i++) {
		a[i] = calloc(columns, 3 * sizeof(char *));
		for (int j = 0; j < columns; j++)
			if (a[i] == NULL)
				free(a[i]);
			else {
				fread(&a[i][j].red, sizeof(char), 1, file);
				fread(&a[i][j].green, sizeof(char), 1, file);
				fread(&a[i][j].blue, sizeof(char), 1, file);
			}
	}
	return a;
}

int **make_selection(int **a, int x1, int x2, int y1, int y2)
{
	int row = 0, col = 0;
	int **selection =
		(int **)calloc(maxval(x1, x2) - minval(x1, x2), sizeof(int *));
	for (int i = minval(x1, x2); i < maxval(x1, x2); i++) {
		selection[row] = calloc(maxval(y1, y2) - minval(y1, y2), sizeof(int *));
		col = 0;
		for (int j = minval(y1, y2); j < maxval(y1, y2); j++) {
			if (selection[row] == NULL)
				free(selection[row]);
			else
				selection[row][col++] = a[i][j];
		}
		row++;
	}
	return selection;
}

colors **make_selection_color(colors **a, int x1, int x2, int y1, int y2)
{
	int row = 0, col = 0;
	colors **selection =
		(colors **)calloc(maxval(x1, x2) - minval(x1, x2), sizeof(int *));
	for (int i = minval(x1, x2); i < maxval(x1, x2); i++) {
		selection[row] =
			calloc(3 * (maxval(y1, y2) - minval(y1, y2)), sizeof(int *));
		col = 0;
		for (int j = minval(y1, y2); j < maxval(y1, y2); j++) {
			if (selection[row] == NULL)
				free(selection[row]);
			else
				selection[row][col++] = a[i][j];
		}
		row++;
	}
	return selection;
}

int **make_selection_binary(int **a, int x1, int x2, int y1, int y2)
{
	int row = 0, col = 0;
	int **selection =
		(int **)calloc(maxval(x1, x2) - minval(x1, x2), sizeof(char *));
	for (int i = minval(x1, x2); i < maxval(x1, x2); i++) {
		selection[row] =
			calloc(maxval(y1, y2) - minval(y1, y2), sizeof(char *));
		col = 0;
		for (int j = minval(y1, y2); j < maxval(y1, y2); j++) {
			if (selection[row] == NULL)
				free(selection[row]);
			else {
				selection[row][col] = a[i][j];
				col++;
			}
		}
		row++;
	}
	return selection;
}

colors **make_selection_color_binary(colors **a, int x1, int x2, int y1, int y2)
{
	int row = 0, col = 0;
	colors **selection =
		(colors **)calloc(maxval(x1, x2) - minval(x1, x2), sizeof(char *));
	for (int i = minval(x1, x2); i < maxval(x1, x2); i++) {
		selection[row] =
			calloc(3 * (maxval(y1, y2) - minval(y1, y2)), sizeof(char *));
		col = 0;
		for (int j = minval(y1, y2); j < maxval(y1, y2); j++) {
			if (selection[row] == NULL)
				free(selection[row]);
			else
				selection[row][col++] = a[i][j];
		}
		row++;
	}
	return selection;
}

int asciiornot(char *s)
{
	char *token;
	token = strtok(s, " ");
	token = strtok(NULL, " ");
	if (strcmp(token, "ascii") == 0)
		return 1;
	else
		return 0;
}

void freeall(int **matrix, int rows)
{
	for (int i = 0; i < rows; i++)
		free(matrix[i]);
	free(matrix);
}

void freeallcolor(colors **matrix, int rows)
{
	for (int i = 0; i < rows; i++)
		free(matrix[i]);
	free(matrix);
}