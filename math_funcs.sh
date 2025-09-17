#!/usr/bin/env bash
set -Eeuo pipefail
# Student: Nguyen Anh Quan | MSSV: 52400310

# Hàm kiểm tra số nguyên
is_integer() {
    local value="$1"
    if [[ "$value" =~ ^-?[0-9]+$ ]]; then
        return 0  # Là số nguyên
    else
        return 1  # Không phải số nguyên
    fi
}

# Hàm tính tổng
sum() {
    if [ $# -eq 0 ]; then
        echo "ERRO: Ham sum() can it nhat 1 tham so!"
        exit 1
    fi
    
    local total=0
    local count=0
    
    for num in "$@"; do
        if ! is_integer "$num"; then
            echo "ERRO: '$num' khong phai la so nguyen hop le!"
            exit 1
        fi
        total=$((total + num))
        count=$((count + 1))
    done
    
    echo "Tong cua $count so: $total"
    return $total
}

# Hàm tính trung bình
avg() {
    if [ $# -eq 0 ]; then
        echo "ERRO: Ham avg() can it nhat 1 tham so!"
        exit 1
    fi
    
    local total=0
    local count=0
    
    for num in "$@"; do
        if ! is_integer "$num"; then
            echo "ERRO: '$num' khong phai la so nguyen hop le!"
            exit 1
        fi
        total=$((total + num))
        count=$((count + 1))
    done
    
    # Tính trung bình (làm tròn)
    local average=$((total / count))
    echo "Trung binh cua $count so: $average"
    return $average
}

# Hàm main để demo
main() {
    echo "========================================="
    echo "MATH FUNCTIONS DEMO"
    echo "Sinh vien: ${1:-Nguyen Anh Quan} - ${2:-52400310}"
    echo "Ngay chay: $(date '+%d/%m/%Y %H:%M:%S')"
    echo "========================================="
    
    # Test với số hợp lệ
    echo "Test 1: sum(1, 2, 3, 4, 5)"
    sum 1 2 3 4 5
    
    echo ""
    echo "Test 2: avg(10, 20, 30)"
    avg 10 20 30
    
    echo ""
    echo "Test 3: sum(-5, 0, 5, 10)"
    sum -5 0 5 10
    
    echo ""
    echo "Test 4: avg(100, 200, 300, 400)"
    avg 100 200 300 400
    
    echo ""
    echo "Test 5: Kiem tra loi - sum(1, abc, 3)"
    if ! sum 1 abc 3 2>/dev/null; then
        echo "Da bat duoc loi nhu mong doi!"
    fi
    
    echo "========================================="
}

# Chế độ interactive để gọi hàm từ terminal
if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    if [ $# -eq 0 ]; then
        main "Nguyen Anh Quan" "52400310"
    else
        case "$1" in
            "sum")
                shift
                sum "$@"
                ;; 
            "avg")
                shift
                avg "$@"
                ;; 
            "demo")
                main "${2:-Nguyen Anh Quan}" "${3:-52400310}"
                ;; 
            *)
                echo "Cach su dung:"
                echo "  ./math_funcs.sh                    # Chay demo"
                echo "  ./math_funcs.sh sum 1 2 3 4        # Tinh tong"
                echo "  ./math_funcs.sh avg 10 20 30       # Tinh trung binh"
                echo "  ./math_funcs.sh demo Ten MSSV      # Chay demo voi ten"
                ;; 
        esac
    fi
fi
