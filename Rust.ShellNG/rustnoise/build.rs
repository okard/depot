// build.rs

use std::old_io::Command;
use std::os;


fn main() {
    let out_dir = os::getenv("OUT_DIR").unwrap();
    let out_dir_path = Path::new(out_dir.as_slice());

    Command::new("gcc").arg("src/linenoise.c")
					   .arg("-fPIC")
                       .arg("-c")
                       .arg("-o")
                       .arg(format!("{}/linenoise.o", out_dir))
                       .status()
                       .unwrap();
    Command::new("ar").arg("crus")
                      .arg("liblinenoise.a")
                      .arg("linenoise.o")
                      .cwd(&out_dir_path)
                      .status()
                      .unwrap();
                      
    println!("cargo:rustc-flags=-L {} -l linenoise:static", out_dir);
}
