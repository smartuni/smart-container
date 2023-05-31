import cx from 'classnames';
import { useState } from "react";
import { useRouter } from "next/router";
import styles from '../styles/Signin.module.css'

export default Signin;

function Signin() {
  const router = useRouter();
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [errors, setErrors] = useState({});
  
  const checkSignIn = () => {
    let errors = {};
    let isValid = true;

    if (!email) 
    {
      errors.email = "Email is required";
      isValid = false;
    } else if (!/\S+@\S+\.\S+/.test(email)) {
      errors.email = 'Email is not valid';
      isValid = false;
    }
    if (!password) 
    {
      errors.password = 'Password is required';
      isValid = false;
    } else if (password.length < 6) {
        errors.password = 'Password must be at least 6 characters';
        isValid = false;
    }
    setErrors(errors);
    return isValid;
  }

  const handleSubmit = (event) => {
    event.preventDefault();
    if (checkSignIn()) {
        console.log({ email, password });
    }
};

  return (
    <div className='bg-malibu-500 h-screen'>
      <div className={styles.signinnew}>
        <main className={cx(styles["form-signin"],"text-center","mt-5")}>
          <h1 className={styles.signin_header}>Sign in</h1>
          <div className="form-floating">
            <form onSubmit={handleSubmit}>
              <div className={styles['form-group']}>
                <label className={styles.label}> 
                  Email:
                  <input 
                    type="loginEmail" 
                    className="form-control" 
                    id="floatingInput" 
                    placeholder="name@example.com" 
                    value={email}
                    onChange={(e) => setEmail(e.target.value)}
                  />
                  {errors.email && <span className={styles.error}>{errors.email}</span>}
                </label>
              </div>
              
              <div className={styles['form-group']}>
                <label className={styles.label}> 
                  Password:
                  <input 
                    type="password" 
                    className="form-control" 
                    id="floatingPassword" 
                    placeholder="Password"
                    value={password} 
                    onChange={(e) => setPassword(e.target.value)}
                  />
                  {errors.password && <span className={styles.error}>{errors.password}</span>}
                </label>
              </div>
            
              <div className={cx(styles.checkbox,"mb")}>
                <label>
                  <input type="checkbox" value="remember-me" /> Remember me
                </label>
              </div>
              <button type="submit">Sign in</button>
              <button>Cancel</button>
              <footer>
                <p>If you don't have an account, please <a href="/signup">sign up here</a>.</p>
              </footer>
            </form>
          </div>
        </main>
      </div>

  </div>
  )
}