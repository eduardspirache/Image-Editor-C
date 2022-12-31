#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "functii.h"

void LOAD(int ***rast, colors ***rastcolor, char *type, int *rows, int *columns,
		  int *maxvalcol, char *fisier, int *okload)
{
	fpos_t position;
	FILE *in = fopen(fisier, "rt");
	if (!in) {
		printf("Failed to load %s\n", fisier);
		*okload = 0;
		return;
	}
	fscanf(in, "%2s", type); // citesc PX
	fscanf(in, "%d%d", columns, rows);
	fscanf(in, "%d", maxvalcol);
	fgetpos(in, &position); // memorez pozitia
	fclose(in);             // inchid fisierul

	if (strcmp(type, "P2") == 0 || strcmp(type, "P3") == 0) {
		FILE *in = fopen(fisier, "rt"); // deschid fisierul in format ASCII
		if (!in) {
			fprintf(stderr, "Failed to load %s\n", fisier);
			return;
		}
		fsetpos(in, &position); // setez pozitia

		if (strcmp(type, "P3") == 0)
			*rastcolor = getcolor(*rows, *columns, in);
		else
			*rast = get_raster(*rows, *columns, in); // citesc rasterul
		fclose(in);
	}

	if (strcmp(type, "P5") == 0 || strcmp(type, "P6") == 0) {
		FILE *in = fopen(fisier, "rb");
		if (!in) {
			fprintf(stderr, "Failed to load %s\n", fisier);
			return;
		}
		fsetpos(in, &position); // setez pozitia dupa PX
		char newline;

		fread(&newline, sizeof(char), 1, in);

		if (strcmp(type, "P6") == 0)
			*rastcolor = getcolor_binary(*rows, *columns, in);
		else
			*rast = get_raster_binary(*rows, *columns, in);
		fclose(in);
	}
	printf("Loaded %s\n", fisier);
	*okload = 1;
}

int **rotate(int **selection, int ang, int selrows, int selcolumns, char *type)
{
	int **a;

	if (ang != 180 && ang != -180) { // afisare col row raster si normal
									 // selectie
		if (strcmp(type, "P2") == 0) {
			a = (int **)calloc(selcolumns, sizeof(int *));
			for (int i = 0; i < selcolumns; i++) {
				a[i] = calloc(selrows, sizeof(int *));
				for (int j = 0; j < selrows; j++)
					if (a[i] == NULL)
						free(a[j]);
			}
		}
		if (strcmp(type, "P5") == 0) {
			a = (int **)calloc(selcolumns, sizeof(char *));
			for (int i = 0; i < selcolumns; i++) {
				a[i] = calloc(selrows, sizeof(char *));
				for (int j = 0; j < selrows; j++)
					if (a[i] == NULL)
						free(a[j]);
			}
		}
		if (ang == 90 || ang == -270)
			for (int i = 0; i < selcolumns; i++)
				for (int j = 0; j < selrows; j++)
					a[i][j] = selection[selrows - 1 - j][i];

		if (ang == -90 || ang == 270)
			for (int i = 0; i < selcolumns; i++)
				for (int j = 0; j < selrows; j++)
					a[i][j] = selection[j][selcolumns - 1 - i];
	}

	if (ang == 180 || ang == -180) { // afisare normala
		if (strcmp(type, "P2") == 0) {
			a = (int **)calloc(selrows, sizeof(int *));
			for (int i = 0; i < selrows; i++) {
				a[i] = calloc(selcolumns, sizeof(int *));
				for (int j = 0; j < selcolumns; j++)
					if (a[i] == NULL)
						free(a[j]);
			}
		}
		if (strcmp(type, "P5") == 0) {
			a = (int **)calloc(selrows, sizeof(char *));
			for (int i = 0; i < selrows; i++) {
				a[i] = calloc(selcolumns, sizeof(char *));
				for (int j = 0; j < selcolumns; j++)
					if (a[i] == NULL)
						free(a[j]);
			}
		}
		for (int i = 0; i < selrows; i++)
			for (int j = 0; j < selcolumns; j++)
				a[i][j] = selection[selrows - 1 - i]
								   [selcolumns - 1 - j]; // afisare normala
	}

	return a;
}

colors **rotatecolor(colors **selectioncolor, int ang, int selrows,
					 int selcolumns, char *type)
{
	colors **a;

	if (ang != 180 && ang != -180) { // afisare col row raster si normal
									 // selectie
		if (strcmp(type, "P3") == 0) {
			a = (colors **)calloc(selcolumns, sizeof(int *));
			for (int i = 0; i < selcolumns; i++) {
				a[i] = calloc(selrows, 3 * sizeof(int *));
				for (int j = 0; j < selrows; j++)
					if (a[i] == NULL)
						free(a[j]);
			}
		}
		if (strcmp(type, "P6") == 0) {
			a = (colors **)calloc(selcolumns, sizeof(char *));
			for (int i = 0; i < selcolumns; i++) {
				a[i] = calloc(selrows, 3 * sizeof(char *));
				for (int j = 0; j < selrows; j++)
					if (a[i] == NULL)
						free(a[j]);
			}
		}

		if (ang == 90 || ang == -270)
			for (int i = 0; i < selcolumns; i++)
				for (int j = 0; j < selrows; j++)
					a[i][j] = selectioncolor[selrows - 1 - j][i];

		if (ang == -90 || ang == 270)
			for (int i = 0; i < selcolumns; i++)
				for (int j = 0; j < selrows; j++)
					a[i][j] = selectioncolor[j][selcolumns - 1 - i];
	}

	if (ang == 180 || ang == -180) { // afisare normala
		if (strcmp(type, "P3") == 0) {
			a = (colors **)calloc(selrows, sizeof(int *));
			for (int i = 0; i < selrows; i++) {
				a[i] = calloc(selcolumns, 3 * sizeof(int *));
				for (int j = 0; j < selcolumns; j++)
					if (a[i] == NULL)
						free(a[j]);
			}
		}
		if (strcmp(type, "P6") == 0) {
			a = (colors **)calloc(selrows, sizeof(char *));
			for (int i = 0; i < selrows; i++) {
				a[i] = calloc(selcolumns, 3 * sizeof(char *));
				for (int j = 0; j < selcolumns; j++)
					if (a[i] == NULL)
						free(a[j]);
			}
		}
		for (int i = 0; i < selrows; i++)
			for (int j = 0; j < selcolumns; j++)
				a[i][j] = selectioncolor[selrows - 1 - i]
										[selcolumns - 1 - j]; // afisare normala
	}
	return a;
}

colors **grayscale(colors **selectcolor, int selrows, int selcols)
{
	for (int i = 0; i < selrows; i++)
		for (int j = 0; j < selcols; j++) {
			double new = (selectcolor[i][j].red + selectcolor[i][j].green +
						  selectcolor[i][j].blue) /
						 3;
			selectcolor[i][j].red = selectcolor[i][j].green =
				selectcolor[i][j].blue = myround(new);
		}
	return selectcolor;
}

colors **sepia(colors **selectcolor, int selrows, int selcols, int max)
{
	for (int i = 0; i < selrows; i++)
		for (int j = 0; j < selcols; j++) {
			double newRed = 0.393 * selectcolor[i][j].red +
							0.769 * selectcolor[i][j].green +
							0.189 * selectcolor[i][j].blue;
			double newGreen = 0.349 * selectcolor[i][j].red +
							  0.686 * selectcolor[i][j].green +
							  0.168 * selectcolor[i][j].blue;
			double newBlue = 0.272 * selectcolor[i][j].red +
							 0.534 * selectcolor[i][j].green +
							 0.131 * selectcolor[i][j].blue;
			selectcolor[i][j].red = minval(myround(newRed), max);
			selectcolor[i][j].green = minval(myround(newGreen), max);
			selectcolor[i][j].blue = minval(myround(newBlue), max);
		}
	return selectcolor;
}

void tempsave(int ***rast, int **selection, colors ***rastcolor,
			  colors **selectioncolor, int x1, int x2, int y1, int y2,
			  int selrows, int selcols, int okselect, char *type)
{
	int i, j, k, l;
	if (okselect) { // daca avem o parte selectata oricum selectia e patrata,
					// deci o integram
		if (strcmp(type, "P3") != 0 && strcmp(type, "P6") != 0)
			for (i = minval(x1, x2), k = 0; i < maxval(x1, x2), k < selrows;
				 i++, k++)
				for (j = minval(y1, y2), l = 0; j < maxval(y1, y2), l < selcols;
					 j++, l++)
					(*rast)[i][j] = selection[k][l];
		else
			for (i = minval(x1, x2), k = 0; i < maxval(x1, x2), k < selrows;
				 i++, k++)
				for (j = minval(y1, y2), l = 0; j < maxval(y1, y2), l < selcols;
					 j++, l++)
					(*rastcolor)[i][j] = selectioncolor[k][l];
	} else { // daca toata imaginea e selectata, atunci memoram modificarile
		if (strcmp(type, "P3") != 0 && strcmp(type, "P6") != 0)
			*rast = selection;
		else
			*rastcolor = selectioncolor;
	} // partea asta merge
}

void makeselection(int ***rast, int ***selection, colors ***rastcolor,
				   colors ***selectioncolor, int x1, int x2, int y1, int y2,
				   int rows, int columns, int *selrows, int *selcols,
				   int okload, int ok90, int *okselect, int *okselall,
				   char *type)
{
	if (!okload)
		printf("No image loaded\n");
	else if (maxval(x1, x2) > rows || maxval(y1, y2) > columns ||
			 minval(x1, x2) < 0 || minval(y1, y2) < 0 || x1 == x2 || y1 == y2) {
		printf("Invalid set of coordinates\n");
	} else {
		if (strcmp(type, "P2") == 0)
			*selection = make_selection(*rast, x1, x2, y1, y2);
		else if (strcmp(type, "P3") == 0)
			*selectioncolor = make_selection_color(*rastcolor, x1, x2, y1, y2);
		else if (strcmp(type, "P5") == 0)
			*selection = make_selection_binary(*rast, x1, x2, y1, y2);
		else if (strcmp(type, "P6") == 0)
			*selectioncolor =
				make_selection_color_binary(*rastcolor, x1, x2, y1, y2);
		*selrows = maxval(x1, x2) - minval(x1, x2);
		*selcols = maxval(y1, y2) - minval(y1, y2);
		*okselect = 1;
		*okselall = 0;
		if (!(ok90 % 2))
			printf("Selected %d %d %d %d\n", y1, x1, y2, x2);
		else
			printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
	}
	if (*selcols == columns && *selrows == rows) {
		*selrows = rows;
		*selcols = columns;
		if (strcmp(type, "P3") != 0 && strcmp(type, "P6") != 0)
			*selection = *rast;
		else
			*selectioncolor = *rastcolor;
		*okselall = 1;
		*okselect = 0;
	}
}

int main(void)
{
	char *file = malloc(100 * sizeof(char));
	int rows, columns;
	int maxvalcol;
	int **rast, **selection;
	colors **rastcolor, **selectioncolor;
	int x1, x2, y1, y2;
	int selrows, selcols;
	int angle;
	int okselect = 0, okselall = 0, okload = 0, okcrop = 0, okrotate = 0,
		ok90 = 0;

	char type[2];
	char *string = malloc(100 * sizeof(char));
	char *function = malloc(9 * sizeof(char));
	char *isitALL = malloc(3 * sizeof(char));

	while (fgets(string, 100, stdin)) {
		sscanf(string, "%s%s", function, isitALL);

		if (strcmp(function, "LOAD") == 0) {
			sscanf(string, "%s%s", function, file);
			LOAD(&rast, &rastcolor, type, &rows, &columns, &maxvalcol, file,
				 &okload);
			if (okload) {
				okselect = 0;
				okselall = 0;
				okcrop = 0;
				okrotate = 0;
				ok90 = 0;
				selrows = rows;
				selcols = columns;
				if (strcmp(type, "P3") != 0 && strcmp(type, "P6") != 0)
					selection = rast;
				else
					selectioncolor = rastcolor;
			}
		} else if (strcmp(function, "SELECT") == 0 &&
				   strcmp(isitALL, "ALL") != 0) {
			int ty = sscanf(string, "%s%d%d%d%d", function, &y1, &x1, &y2, &x2);
			if (ok90 % 2) {
				myswap(&x1, &y1);
				myswap(&x2, &y2);
			}
			if (ty < 5)
				printf("Invalid command\n");
			else
				makeselection(&rast, &selection, &rastcolor, &selectioncolor,
							  x1, x2, y1, y2, rows, columns, &selrows, &selcols,
							  okload, ok90, &okselect, &okselall, type);
		}

		else if (strcmp(function, "SELECT") == 0 &&
				 strcmp(isitALL, "ALL") == 0) {
			if (okload) {
				selrows = rows;
				selcols = columns;
				if (strcmp(type, "P3") != 0 && strcmp(type, "P6") != 0)
					selection = rast;
				else
					selectioncolor = rastcolor;
				printf("Selected ALL\n");
				okselall = 1;
				okselect = 0;
			} else
				printf("No image loaded\n");
		}

		else if (strcmp(function, "CROP") == 0) {
			if (okload) {
				okselect = 0;
				rast = selection;
				rastcolor = selectioncolor;
				rows = selrows;
				columns = selcols;
				printf("Image cropped\n");
				okcrop = 1;
			} else
				printf("No image loaded\n");
		}

		else if (strcmp(function, "ROTATE") == 0) {
			sscanf(string, "%s%d", function, &angle);
			if (!okload)
				printf("No image loaded\n");
			else if (angle == 360 || angle == -360 || angle == 0)
				printf("Rotated %d\n", angle);
			else {
				if (selrows != selcols && okcrop == 0 && okselect &&
					okselall == 0)
					printf("The selection must be square\n");
				else if (angle % 90 != 0 || angle == 0)
					printf("Unsupported rotation angle\n");
				else {
					if ((!okselect || ((okselect || okselall) && okcrop)) &&
						(ok90 % 2)) {
						if (strcmp(type, "P3") != 0 && strcmp(type, "P6") != 0)
							selection = rotate(selection, angle, selcols,
										   selrows, type);
						else
							selectioncolor = rotatecolor(
								selectioncolor, angle, selcols, selrows, type);
					} else {
						if (strcmp(type, "P3") != 0 && strcmp(type, "P6") != 0)
							selection = rotate(selection, angle, selrows,
										   selcols, type);
						else
							selectioncolor = rotatecolor(
								selectioncolor, angle, selrows, selcols, type);
					}
					if (!okselect || ((okselect || okselall) && okcrop)) {
						if (angle == 90 || angle == -270)
							ok90++;
						if (angle == -90 || angle == 270)
							ok90--;
					}

					if (ok90 % 2 == 0)
						tempsave(&rast, selection, &rastcolor, selectioncolor,
								 x1, x2, y1, y2, selrows, selcols, okselect,
								 type);
					else
						tempsave(&rast, selection, &rastcolor, selectioncolor,
								 x1, x2, y1, y2, selcols, selrows, okselect,
								 type);
					printf("Rotated %d\n", angle);
					okrotate = 1;
				}
			}
		}

		else if (strcmp(function, "GRAYSCALE") == 0) {
			if (okload) {
				if (strcmp(type, "P3") != 0 && strcmp(type, "P6") != 0)
					printf("Grayscale filter not available\n");
				else {
					if (ok90 % 2 == 0)
						selectioncolor =
							grayscale(selectioncolor, selrows, selcols);
					else
						selectioncolor =
							grayscale(selectioncolor, selcols, selrows);

					if (ok90 % 2 == 0)
						tempsave(&rast, selection, &rastcolor, selectioncolor,
								 x1, x2, y1, y2, selrows, selcols, okselect,
								 type);
					else
						tempsave(&rast, selection, &rastcolor, selectioncolor,
								 x1, x2, y1, y2, selcols, selrows, okselect,
								 type);
					printf("Grayscale filter applied\n");
				}
			} else
				printf("No image loaded\n");
		}

		else if (strcmp(function, "SEPIA") == 0) {
			if (okload) {
				if (strcmp(type, "P3") != 0 && strcmp(type, "P6") != 0)
					printf("Sepia filter not available\n");
				else {
					if (ok90 % 2 == 0)
						selectioncolor =
							sepia(selectioncolor, selrows, selcols, maxvalcol);
					else
						selectioncolor =
							sepia(selectioncolor, selcols, selrows, maxvalcol);
					if (ok90 % 2 == 0)
						tempsave(&rast, selection, &rastcolor, selectioncolor,
								 x1, x2, y1, y2, selrows, selcols, okselect,
								 type);
					else
						tempsave(&rast, selection, &rastcolor, selectioncolor,
								 x1, x2, y1, y2, selcols, selrows, okselect,
								 type);
					printf("Sepia filter applied\n");
				}
			} else
				printf("No image loaded\n");
		}

		else if (strcmp(function, "SAVE") == 0) {
			char *filename = malloc(100 * sizeof(char));
			char *ascii = malloc(6 * sizeof(char));
			int okascii = 0;
			sscanf(string, "%s%s%s", function, filename, ascii);
			if (strcmp(ascii, "ascii") == 0)
				okascii = 1;
			char *temptype = malloc(2 * sizeof(char));
			if (okascii) {
				if (!strcmp(type, "P6"))
					temptype = "P3";
				else if (!strcmp(type, "P5"))
					temptype = "P2";
				else
					temptype = type;
			} else {
				if (!strcmp(type, "P3"))
					temptype = "P6";
				else if (!strcmp(type, "P2"))
					temptype = "P5";
				else
					temptype = type;
			}
			fpos_t position;
			if (okload) {
				FILE *fp;
				fp = fopen(filename, "wt");

				if (ok90 % 2 == 0)
					tempsave(&rast, selection, &rastcolor, selectioncolor, x1,
							 x2, y1, y2, selrows, selcols, okselect, type);
				else
					tempsave(&rast, selection, &rastcolor, selectioncolor, x1,
							 x2, y1, y2, selcols, selrows, okselect, type);

				if (ok90 % 2 == 0)
					fprintf(fp, "%s\n%d %d\n%d\n", temptype, columns, rows,
							maxvalcol);
				else
					fprintf(fp, "%s\n%d %d\n%d\n", temptype, rows, columns,
							maxvalcol);

				fgetpos(fp, &position);
				fclose(fp);

				fp = fopen(filename, "at");
				if (!strcmp(temptype, "P2")) {
					if (!(ok90 % 2))
						for (int i = 0; i < rows; i++) {
							for (int j = 0; j < columns; j++)
								fprintf(fp, "%d ", rast[i][j]);
							fprintf(fp, "\n");
						}
					else
						for (int i = 0; i < columns; i++) {
							for (int j = 0; j < rows; j++)
								fprintf(fp, "%d ", rast[i][j]);
							fprintf(fp, "\n");
						}
				} else if (!strcmp(temptype, "P3")) {
					if (!(ok90 % 2))
						for (int i = 0; i < rows; i++) {
							for (int j = 0; j < columns; j++)
								fprintf(fp, "%d %d %d ", rastcolor[i][j].red,
										rastcolor[i][j].green,
										rastcolor[i][j].blue);
							fprintf(fp, "\n");
						}
					else
						for (int i = 0; i < columns; i++) {
							for (int j = 0; j < rows; j++)
								fprintf(fp, "%d %d %d ", rastcolor[i][j].red,
										rastcolor[i][j].green,
										rastcolor[i][j].blue);
							fprintf(fp, "\n");
						}
				}
				fclose(fp);

				fp = fopen(filename, "ab");
				if (!strcmp(temptype, "P5")) {
					if (!(ok90 % 2))
						for (int i = 0; i < rows; i++)
							for (int j = 0; j < columns; j++)
								fwrite(&rast[i][j], sizeof(char), 1, fp);
					else
						for (int i = 0; i < columns; i++)
							for (int j = 0; j < rows; j++)
								fwrite(&rast[i][j], sizeof(char), 1, fp);
				} else if (!strcmp(temptype, "P6")) {
					if (!(ok90 % 2))
						for (int i = 0; i < rows; i++)
							for (int j = 0; j < columns; j++) {
								fwrite(&rastcolor[i][j].red, sizeof(char), 1,
									   fp);
								fwrite(&rastcolor[i][j].green, sizeof(char), 1,
									   fp);
								fwrite(&rastcolor[i][j].blue, sizeof(char), 1,
									   fp);
							}
					else
						for (int i = 0; i < columns; i++)
							for (int j = 0; j < rows; j++) {
								fwrite(&rastcolor[i][j].red, sizeof(char), 1,
									   fp);
								fwrite(&rastcolor[i][j].green, sizeof(char), 1,
									   fp);
								fwrite(&rastcolor[i][j].blue, sizeof(char), 1,
									   fp);
							}
				}
				fclose(fp);

				printf("Saved %s\n", filename);
				free(filename);
				free(ascii);
				okascii = 0;
			} else
				printf("No image loaded\n");
		}

		else if (strcmp(function, "EXIT\n") == 0) {
			if (!okload)
				printf("No image loaded\n");
			else {
				if (strcmp(type, "P3") != 0 && strcmp(type, "P6") != 0) {
					freeall(rast, rows);
					if (okselect)
						freeall(selection, selrows);
				} else {
					freeallcolor(rastcolor, rows);
					if (okselect)
						freeallcolor(selectioncolor, selrows);
				}
			}
			free(file);
			free(string);
			free(function);
			free(isitALL);
			exit(0);
		}

		else if (strcmp(function, "EXIT") == 0) {
			if (!okload)
				printf("No image loaded\n");
			else {
				if (strcmp(type, "P3") != 0 && strcmp(type, "P6") != 0) {
					freeall(rast, rows);
					if (okselect)
						freeall(selection, selrows);
				} else {
					freeallcolor(rastcolor, rows);
					if (okselect)
						freeallcolor(selectioncolor, selrows);
				}
			}
			free(file);
			free(string);
			free(function);
			free(isitALL);
			exit(0);
		}

		else
			printf("Invalid command\n");
	}
	return 0;
}