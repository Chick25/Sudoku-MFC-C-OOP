#include "pch.h"
#include "Banco.h"
#include "random"
Banco::Banco()
{
	std::random_device rd; // Sinh s? ng?u nhiên th?c s? (n?u có)
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_int_distribution<> dist(0, 9);
	control = 1;

	int xm = 50, ym = 50; // toa do ban co
	int d = 40;//kich thuoc ban co
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			mang[i][j].setHcn(xm + j * d, ym + i * d, xm + j * d + d, ym + i * d + d);
		}
	}
	
	int dem1 = 0;
	int rani1 = 0, ranj1 = 0;
	while (dem1 < 9)
	{
		rani1 = dist(gen);
		ranj1 = dist(gen);
		if (isDatSo(rani1, ranj1, mang[rani1][ranj1].so) == false)
		{
			
			mang[rani1][ranj1].so = 1;
			
			dem1++;
			
			ngauNhien();
			
		}
	}
	
	
}

void Banco::draw(CClientDC* dc)
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			mang[i][j].draw(dc);
			//mang[i][j].bcolor = 1;
		}
	}
}

void Banco::draw(CPaintDC* dc)
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			mang[i][j].draw(dc);
			//mang[i][j].bcolor = 1;
		}
	}
}

bool Banco::isDatSo(int mi, int mj, int num)
{
	//ktra hang
	for (int x = 0; x < 9; x++) {
		if (mang[mi][x].so == num) {
			return false;
		}
	}
	//ktra cot
	for (int y = 0; y < 9; y++) {
		if (mang[y][mj].so == num) {
			return false;
		}
	}
	//ktra pham vi 3x3
	int startmi = (mi / 3) * 3;
	int startmj = (mj / 3) * 3;
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (mang[startmi + x][startmj + y].so == num) {
				return false;
			}
		}
	}
	return true;
}

void Banco::ngauNhien()
{
	/*
	std::random_device rd; // Sinh s? ng?u nhiên th?c s? (n?u có)
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_int_distribution<> dist(0, 9);
	//srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int num = dist(gen);
			while (!isDatSo(i, j, num)) {
				//num = rand() % 9 + 1;
				num = dist(gen);
			}
			mang[i][j].so = num;
		}
	}
	*/

	/*
	int board[9][9] = { 0 };

	// T?o b?ng Sudoku hoàn ch?nh (m?t cách ??n gi?n)
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int num = (i * 3 + i / 3 + j) % 9 + 1; // Công th?c t?o b?ng c? b?n
			board[i][j] = num;
		}
	}
	
	// Xáo tr?n hàng và c?t trong t?ng nhóm 3x3
	std::random_device rd;
	std::mt19937 gen(rd());
	for (int i = 0; i < 9; i += 3) {
		std::shuffle(&board[i][0], &board[i + 3][0], gen); // Xáo tr?n hàng
		for (int j = 0; j < 9; j += 3) {
			std::shuffle(&board[0][j], &board[0][j + 3], gen); // Xáo tr?n c?t
		}
	}

	// Chuy?n giá tr? t? `board` vào `mang`
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			mang[i][j].so = board[i][j];
			mang[i][j].dong = 0; // ?ánh d?u ?ây là ô c? ??nh
		}
	}

	// Xóa ng?u nhiên 40 ô ?? t?o b?ng Sudoku
	std::uniform_int_distribution<> dist(0, 8);
	for (int i = 0; i < 40; i++) {
		int x = dist(gen);
		int y = dist(gen);
		mang[x][y].so = 0; // Xóa s?
		mang[x][y].dong = 1; // ?ánh d?u là ô tr?ng
	}
	*/
	//Notice: Sau day la thuat toan quay lui, hoi kho nen co tham khao
	//dung phong bat

	std::random_device rd; // Sinh s? ng?u nhiên th?c s?
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_int_distribution<> dist(1, 9); // S? t? 1 ??n 9

	// ??t t?t c? các ô ban ??u b?ng 0
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			mang[i][j].so = 0;
			
		}
	}

	// T?o b?ng Sudoku b?ng cách ?i?n s? h?p l?
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int num = dist(gen); // S? ng?u nhiên ban ??u
			int attempts = 0; // ??m s? l?n th? s?

			// Tìm s? h?p l? cho ô hi?n t?i
			while (!isDatSo(i, j, num)) {
				num = dist(gen);
				attempts++;
				if (attempts > 20) {
					// N?u không tìm ???c s? h?p l? sau nhi?u l?n th?, reset hàng
					for (int k = 0; k < 9; k++) {
						mang[i][k].so = 0;
					}
					j = -1; // Quay l?i ??u hàng
					break;
				}
			}

			// N?u s? h?p l?, ??t vào b?ng
			if (attempts <= 20) {
				mang[i][j].so = num;
			}
		}
	}

	// Xóa ng?u nhiên 40 ô ?? t?o b?ng Sudoku
	std::uniform_int_distribution<> distIndex(0, 8); // Ch? s? hàng và c?t
	int removed = 0;
	while (removed < 40) {
		int x = distIndex(gen);
		int y = distIndex(gen);

		if (mang[x][y].so != 0) { // Ch? xóa n?u ô ?ó ch?a b? xóa
			mang[x][y].so = 0;
			mang[x][y].dong = 1; // ?ánh d?u là ô tr?ng
			removed++;
		}
	}
}
void Banco::showPopup(CPoint p, CWnd* pWnd, int mi, int mj)
{
	if (mang[mi][mj].dong != 1) {
		return; // Không hiển thị menu nếu không phải ô trống
	}

	CMenu menu;
	menu.CreatePopupMenu();

	// Sắp xếp các mục menu thành 3x3
	int menuId = 1001; // ID bắt đầu từ 1001
	for (int row = 0; row < 3; row++) {
		CMenu subMenu;  // Tạo submenu cho mỗi hàng
		subMenu.CreatePopupMenu();

		// Mỗi hàng có 3 mục
		for (int col = 0; col < 3; col++) {
			int num = row * 3 + col + 1;  // Tính toán số từ 1 đến 9
			CString item;
			item.Format(_T("%d"), num);
			subMenu.AppendMenu(MF_STRING, menuId++, item); // Thêm mục vào submenu với ID duy nhất
		}

		// Thêm submenu vào menu chính
		menu.AppendMenu(MF_POPUP, (UINT_PTR)subMenu.m_hMenu, _T("")); // Đặt menu con vào menu chính
	}

	hoveredRow = mi;
	hoveredCol = mj;

	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, pWnd);
}
void Banco::chonSo(int num)
{
	if (hoveredRow >= 0 && hoveredCol >= 0 && mang[hoveredRow][hoveredCol].dong == 1) {
		mang[hoveredRow][hoveredCol].so = num;
		mang[hoveredRow][hoveredCol].dong = 0; // Không còn là ô trống
		hoveredRow = -1;
		hoveredCol = -1;
	}
}
/*
void Banco::keyPress(CPoint p, CPaintDC* dc)
{
	
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (mang[i][j].kttronghinh(p)) {
				if (mang[i][j].dong == 1) {//neu la o trong
					CString nhap;
					if (AfxMessageBox(_T("Nh?p s? t? 1 ??n 9:"), MB_OKCANCEL) == IDOK) {
						nhap = _T("5");
					}

					int num = _ttoi(nhap);
					if (num >= 1 && num <= 9) {
						if (isDatSo(i, j, num)) {
							mang[i][j].so = num;
							mang[i][j].dong = 0;
							mang[i][j].draw(dc);
						}else {
							AfxMessageBox(_T("S? không h?p l? trong hàng, c?t, ho?c vùng 3x3!"));
						}
					}else {
						AfxMessageBox(_T("Ch? nh?p s? t? 1 ??n 9!"));
					}
				}else {
					AfxMessageBox(_T("Ô này không th? ch?nh s?a!"));
				}
				return;
			}
		}
	}
}
*/
